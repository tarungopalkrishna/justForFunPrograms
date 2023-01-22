#include <librdkafka/rdkafkacpp.h>
#include <sys/time.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

// Defining macros
// #define KNEST_DEBUG

// Who'd have thought I'd care about compatability
#ifdef _MSC_VER
#include "../win32/wingetopt.h"
#elif _AIX
#include <unistd.h>
#else
#include <getopt.h>
#include <unistd.h>
#endif

// NOP operations
#define NOP() ({ (void)0; })

// Set the program execution handlers
static volatile sig_atomic_t run = 1;
static void sigterm(int sig) { run = 0; }

static void print_time() {
    struct timeval tv;
    char buf[64];
    gettimeofday(&tv, NULL);
    strftime(buf, sizeof(buf) - 1, "%Y-%m-%d %H:%M:%S", localtime(&tv.tv_sec));
    fprintf(stderr, "%s.%03d: ", buf, (int)(tv.tv_usec / 1000));
}
class ExampleEventCb : public RdKafka::EventCb {
   public:
    void event_cb(RdKafka::Event &event) {
        print_time();

        switch (event.type()) {
            case RdKafka::Event::EVENT_ERROR:
                if (event.fatal()) {
                    std::cerr << "FATAL ";
                    run = 0;
                }
                std::cerr << "ERROR (" << RdKafka::err2str(event.err()) << "): " << event.str() << std::endl;
                break;

            case RdKafka::Event::EVENT_STATS:
                std::cerr << "\"STATS\": " << event.str() << std::endl;
                break;

            case RdKafka::Event::EVENT_LOG:
                fprintf(stderr, "LOG-%i-%s: %s\n", event.severity(), event.fac().c_str(), event.str().c_str());
                break;

            case RdKafka::Event::EVENT_THROTTLE:
                std::cerr << "THROTTLED: " << event.throttle_time() << "ms by " << event.broker_name() << " id "
                          << (int)event.broker_id() << std::endl;
                break;

            default:
                std::cerr << "EVENT " << event.type() << " (" << RdKafka::err2str(event.err()) << "): " << event.str()
                          << std::endl;
                break;
        }
    }
};

class Consumer {
   private:
    std::vector<std::string> topics;
    std::string brokers;
    std::string group_id;
    // Do I need make this global to the class?
    std::string error_string;
    RdKafka::Conf *conf;
    RdKafka::KafkaConsumer *consumer;
    int64_t msg_bytes = 0;
    bool exit_eof = false;
    // Edit the data types of this
    long msg_cnt = 0;
    int verbosity = 1;
    int eof_cnt = 0;
    int partition_cnt = 0;

   public:
    Consumer() { this->conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL); }

    ~Consumer() {
        this->consumer->close();
        delete consumer;

        std::cerr << "% Consumed " << this->msg_cnt << " messages (" << this->msg_bytes << " bytes)" << std::endl;

        /*
         * Wait for RdKafka to decommission.
         * This is not strictly needed (with check outq_len() above), but
         * allows RdKafka to clean up all its resources before the application
         * exits so that memory profilers such as valgrind wont complain about
         * memory leaks.
         */
        RdKafka::wait_destroyed(5000);
    }

    void set_defaults() {
        if (this->conf->set("group.id", "test-id", this->error_string) != RdKafka::Conf::CONF_OK) {
            std::cerr << this->error_string << std::endl;
            exit(1);
        }

        /*
         * Yes technically this config is deprecated, but I think the underlying libraries
         * haven't been updated.
         */
        this->conf->set("metadata.broker.list", "localhost:9092", this->error_string);

        // FIXME: Change this!
        this->topics.push_back(std::string("test.topic"));
        // this->topics.push_back("test");
    }

    bool create_consumer() {
        this->consumer = RdKafka::KafkaConsumer::create(conf, error_string);
        if (!consumer) {
            std::cerr << "Failed to create consumer: " << error_string << std::endl;
            return false;
            // exit(1);
        }
        // Free up the memory
        delete this->conf;

        return true;
    }

    bool connect() {
        // Print all the topics
        for(auto v: this->topics){
            std::cout << v << "|";
        }
        std::cout << std::endl;
        int a = 1;
        int b = 2;
        int c = 3;
        int d = 4;
        int e = 5;
        // const std::vector<std::string> &tp = {"test.topic"};
        // std::cout << "this->consumer:" << typeid(this->consumer).name() << std::endl;
        // std::cout << "this->topics:" << typeid(this->topics).name() << std::endl;

        RdKafka::ErrorCode err = this->consumer->subscribe(this->topics);

        // Corresponding c code
        // std::cout << "The number of topics are: " << (int)topics.size() << std::endl;
        // for(unsigned int i=0; i < topics.size(); i++){
        //     std::cout << topics[i].c_str() << std::endl;
        // }
        // std::cout << "Hello1" << std::endl;
        if (err) {
            std::cerr << "Failed to subscribe to " << this->topics.size() << " topics: " << RdKafka::err2str(err)
                      << std::endl;
            // std::cout << "Hello1.1" << std::endl;
            return false;
        }
        // std::cout << "Hello1.2" << std::endl;
        return true;
    }

    void msg_consume(RdKafka::Message *message, void *opaque) {
        switch (message->err()) {
            // Timeout due to no message or event in timeout_ms
            case RdKafka::ERR__TIMED_OUT:
                break;

            case RdKafka::ERR_NO_ERROR:
                /* Real message */
                this->msg_cnt++;
                this->msg_bytes += message->len();
                if (this->verbosity >= 3) std::cerr << "Read msg at offset " << message->offset() << std::endl;
                RdKafka::MessageTimestamp ts;
                ts = message->timestamp();
                if (this->verbosity >= 2 && ts.type != RdKafka::MessageTimestamp::MSG_TIMESTAMP_NOT_AVAILABLE) {
                    std::string tsname = "?";
                    if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_CREATE_TIME)
                        tsname = "create time";
                    else if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_LOG_APPEND_TIME)
                        tsname = "log append time";
                    std::cout << "Timestamp: " << tsname << " " << ts.timestamp << std::endl;
                }
                if (this->verbosity >= 2 && message->key()) {
                    std::cout << "Key: " << *message->key() << std::endl;
                }
                if (this->verbosity >= 1) {
                    printf("%.*s\n", static_cast<int>(message->len()), static_cast<const char *>(message->payload()));
                }
                break;

            case RdKafka::ERR__PARTITION_EOF:
                /* Last message */
                if (this->exit_eof && ++(this->eof_cnt) == this->partition_cnt) {
                    std::cerr << "%% EOF reached for all " << this->partition_cnt << " partition(s)" << std::endl;
                    run = 0;
                }
                break;

            case RdKafka::ERR__UNKNOWN_TOPIC:
            case RdKafka::ERR__UNKNOWN_PARTITION:
                std::cerr << "Consume failed: " << message->errstr() << std::endl;
                run = 0;
                break;

            default:
                /* Errors */
                std::cerr << "Consume failed: " << message->errstr() << std::endl;
                run = 0;
        }
    }

    void consume() {
        while (run) {
            RdKafka::Message *msg = consumer->consume(1000);
            msg_consume(msg, NULL);
            delete msg;
        }
    }

    void close() {
        this->consumer->close();
        delete consumer;

        std::cerr << "% Consumed " << this->msg_cnt << " messages (" << this->msg_bytes << " bytes)" << std::endl;

        /*
         * Wait for RdKafka to decommission.
         * This is not strictly needed (with check outq_len() above), but
         * allows RdKafka to clean up all its resources before the application
         * exits so that memory profilers such as valgrind wont complain about
         * memory leaks.
         */
        RdKafka::wait_destroyed(5000);
    }

    void print_metadata() { std::cout << "Name of the consumer is:" << this->consumer->name() << std::endl; }

    void dump_config() {
        std::list<std::string> *dump;
        dump = this->conf->dump();
        std::cout << "# Global config" << std::endl;

        for (std::list<std::string>::iterator it = dump->begin(); it != dump->end();) {
            std::cout << *it << " = ";
            it++;
            std::cout << *it << std::endl;
            it++;
        }
        std::cout << std::endl;

        exit(0);
    }

   protected:
};

int main(int argc, char const *argv[]) {
    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);
    Consumer c = Consumer();
    c.set_defaults();
    c.create_consumer();
#ifdef KNEST_DEBUG
    printf("The librdkafka version is %s (0x%08x)", RdKafka::version_str().c_str(), RdKafka::version());
    c.dump_config();
#endif
    c.connect();
    std::cout<< "1" << std::endl;
    c.consume();
    return 0;
}
