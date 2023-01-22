#include <iostream>
// #include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <sys/time.h>

#ifdef _MSC_VER
#include "../win32/wingetopt.h"
#elif _AIX
#include <unistd.h>
#else
#include <getopt.h>
#include <unistd.h>
#endif

// Docs for librdkafka
// https://docs.confluent.io/5.5.1/clients/librdkafka/md_INTRODUCTION.html#introduction-to-librdkafka---the-apache-kafka-cc-client-library

// void configure_producer(char *hostname)
// {
//     char err_string[512];
//     rd_kafka_conf_t *conf = rd_kafka_conf_new();
//     if (hostname){
//         std::cout << "The hostname is: " << hostname << std::endl;
//         if (rd_kafka_conf_set(conf, "client.id", hostname, err_string, sizeof(err_string)) != RD_KAFKA_CONF_OK) {
//             fprintf(stderr, "%% -> %s\n", err_string);
//             exit(1);
//         }
//         if (rd_kafka_conf_set(conf, "bootstrap.servers", "localhost:9092", err_string, sizeof(err_string)) != RD_KAFKA_CONF_OK){
//             fprintf(stderr, "%% %s\n", err_string);
//             exit(1);
//         }

//         rd_kafka_topic_conf_t *topic_conf = rd_kafka_topic_conf_new();

//         if (rd_kafka_topic_conf_set(topic_conf, "acks", "all", err_string, sizeof(err_string)) != RD_KAFKA_CONF_OK) {
//             fprintf(stderr, "%% %s\n", err_string);
//             exit(1);
//         }

//         /* Create Kafka producer handle */
//         rd_kafka_t *rk;
//         if (!(rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, err_string, sizeof(err_string)))) {
//             fprintf(stderr, "%% Failed to create new producer: %s\n", err_string);
//             exit(1);
//         }
//     } else {
//         fprintf(stderr, "No hostname!");
//         exit(1);
//     }
// }

// void producer(){
//     rd_kafka_topic_t *rkt = rd_kafka_topic_new(rk, topic, topic_conf);

//     if (rd_kafka_produce(rkt, RD_KAFKA_PARTITION_UA,
//                          RD_KAFKA_MSG_F_COPY,
//              payload, payload_len,
//                          key, key_len,
//        NULL) == -1) {
//       fprintf(stderr, "%% Failed to produce to topic %s: %s\n",
//      topic, rd_kafka_err2str(rd_kafka_errno2err(errno)));
//     }
// }

// rd_kafka_resp_err_t sync_produce (rd_kafka_t *rk,rd_kafka_topic_t *rkt, int32_t partition,
//                                   void *payload, size_t len,
//                                   const void *key, size_t keylen) {

//     rd_kafka_resp_err_t err = RD_KAFKA_RESP_ERR__BEGIN;
//     std::cout << "This should technically produce a message" << std::endl;
//     if (rd_kafka_produce(rkt, partition, 0, payload, len,
//                          key, keylen, &err) == -1)
//             return rd_kafka_errno2err(errno);
//     while (err == -12345)
//             rd_kafka_poll(rk, 1000);
//     return err;
// }


// static void msg_delivered (rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque) {
//     if (rkmessage->_private) {
//         rd_kafka_resp_err_t *errp = (rd_kafka_resp_err_t *)rkmessage->_private;
//         *errp = rkmessage->err;
//     }
// }

// void my_init_code (void) {
//         char errstr[512];
//         rd_kafka_conf_t *rk_conf = rd_kafka_conf_new();

//         /* Set delivery report callback */
//         rd_kafka_conf_set_dr_msg_cb(rk_conf, msg_delivered);
//         /* Minimize wait-for-larger-batch delay (since there will be no batching) */
//         rd_kafka_conf_set(rk_conf, "queue.buffering.max.ms", "1", errstr, sizeof(errstr));
//         /* Minimize wait-for-socket delay (otherwise you will lose 100ms per message instead just the RTT) */
//         // rd_kafka_conf_set(rk_conf, "socket.blocking.max.ms", "1", errstr, sizeof(errstr));

//         char err_string[512];
//         rd_kafka_t *rk = rd_kafka_new(RD_KAFKA_PRODUCER, rk_conf, errstr, sizeof(errstr));
//         if (!rk)
//                 fprintf(stderr , "--> %s", errstr);


//         if (rd_kafka_conf_set(rk_conf, "client.id", "localhost:9092", err_string, sizeof(err_string)) != RD_KAFKA_CONF_OK) {
//             fprintf(stderr, "%% -> %s\n", err_string);
//             exit(1);
//         }
//         if (rd_kafka_conf_set(rk_conf, "bootstrap.servers", "localhost:9092", err_string, sizeof(err_string)) != RD_KAFKA_CONF_OK){
//             fprintf(stderr, "%% %s\n", err_string);
//             exit(1);
//         }

//         rd_kafka_topic_conf_t *topic_conf = rd_kafka_topic_conf_new();

//         // if (rd_kafka_topic_conf_set(topic_conf, "acks", "all", err_string, sizeof(err_string)) != RD_KAFKA_CONF_OK) {
//         //     fprintf(stderr, "%% %s\n", err_string);
//         //     exit(1);
//         // }

//         // Payload
//         std::string payload = "test payload";
//         size_t payload_size = payload.length();

//         /* create topics, etc.. */
//         // rd_kafka_topic_conf_t *topic_conf = rd_kafka_topic_conf_new();
//         rd_kafka_topic_t *rkt = rd_kafka_topic_new(rk, "test.topic", topic_conf);
//         sync_produce(rk, rkt, 0, &payload, payload_size, "null", 4);
// }



// class Connector: public RdKafka::Handle{

// private:
//     std::string handle_name = "test_handler";
//     std::string memberid = nullptr;

// public:

//     Connector(){
//         std::cout << "Hey this is the constructor of the Connector class" << std::endl;

//     }

//     const std::string name() const override{
//         return this->handle_name;
//     }

//     const std::string memberid() const override{
//         return this->memberid;
//     }


//     // Add arguments to the function
//     bool connect_to_kafka(){


//     }



//     ~Connector(){
//         std::cout << "Hey this is the destructor of the Connector class" << std::endl;
//     }


// protected:

// };



// void my_init_code(){
//     std::string error_string = "\0";

//     RdKafka::Conf::ConfType config = RdKafka::Conf::ConfType(RdKafka::Conf::CONF_TOPIC);
//     RdKafka::Conf *consumer_config = RdKafka::Conf::create(config);
//     RdKafka::Consumer *consumer = RdKafka::Consumer::create(consumer_config , error_string);

//     if(!consumer){
//         fprintf(stderr, "%s\n", error_string);

//     }

//     // RdKafka::Handle *handle = RdKafka::Handle();

//     // RdKafka::Topic::create()
//     // while (true){
//     //     consumer->start("test.topic", 0, 0);
//     // }

// }


static volatile sig_atomic_t run = 1;
static bool exit_eof             = false;
static int eof_cnt               = 0;
static int partition_cnt         = 0;
static int verbosity             = 1;
static long msg_cnt              = 0;
static int64_t msg_bytes         = 0;

static void sigterm(int sig) {
  run = 0;
}


class ExampleDeliveryReportCb : public RdKafka::DeliveryReportCb {
 public:
  void dr_cb(RdKafka::Message &message) {
    /* If message.err() is non-zero the message delivery failed permanently
     * for the message. */
    if (message.err())
      std::cerr << "% Message delivery failed: " << message.errstr()
                << std::endl;
    else
      std::cerr << "% Message delivered to topic " << message.topic_name()
                << " [" << message.partition() << "] at offset "
                << message.offset() << std::endl;
  }
};

int test_producer(std::string brokers, std::string topic, std::string payload){
    // std::string bootstrap_server = "localhost:9092";
    // std::string topic = "test.topic";
    // std::string groupid = "test-group";
    std::string error_string;

    // Create the config
    // Global configuration
    RdKafka::Conf *global_config = RdKafka::Conf::create(RdKafka::Conf::ConfType::CONF_GLOBAL);
    if(global_config->set("bootstrap.servers", brokers, error_string) != RdKafka::Conf::CONF_OK){
        std::cerr << error_string << std::endl;
        exit(1);
    }

    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);

    ExampleDeliveryReportCb del_cb;

    if (global_config->set("dr_cb", &del_cb, error_string) != RdKafka::Conf::CONF_OK) {
        std::cerr << error_string << std::endl;
        exit(1);
    }



    RdKafka::Producer *producer = RdKafka::Producer::create(global_config, error_string);
    if(!producer){
        std::cerr << "Failed to create producer: " << error_string << std::endl;
        exit(1);
    }

    // Is this how we deallocate memory in cpp?
    delete global_config;


    // RdKafka::ErrorCode err = producer->produce(topic,
    //                             RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY,
    //                             const_cast<char *> payload, payload.length())
    for (std::string line; run && std::getline(std::cin, line);) {
        if (line.empty()) {
          producer->poll(0);
          continue;
        }

        /*
         * Send/Produce message.
         * This is an asynchronous call, on success it will only
         * enqueue the message on the internal producer queue.
         * The actual delivery attempts to the broker are handled
         * by background threads.
         * The previously registered delivery report callback
         * is used to signal back to the application when the message
         * has been delivered (or failed permanently after retries).
         */
  retry:
        RdKafka::ErrorCode err = producer->produce(
                /* Topic name */
                topic,
                /* Any Partition: the builtin partitioner will be
                 * used to assign the message to a topic based
                 * on the message key, or random partition if
                 * the key is not set. */
                RdKafka::Topic::PARTITION_UA,
                /* Make a copy of the value */
                RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
                /* Value */
                const_cast<char *>(line.c_str()), line.size(),
                /* Key */
                NULL, 0,
                /* Timestamp (defaults to current time) */
                0,
                /* Message headers, if any */
                NULL,
                /* Per-message opaque value passed to
                 * delivery report */
                NULL);

        if (err != RdKafka::ERR_NO_ERROR) {
            std::cerr << "% Failed to produce to topic " << topic << ": "
                    << RdKafka::err2str(err) << std::endl;

            if (err == RdKafka::ERR__QUEUE_FULL) {
              /* If the internal queue is full, wait for
               * messages to be delivered and then retry.
               * The internal queue represents both
               * messages to be sent and messages that have
               * been sent or failed, awaiting their
               * delivery report callback to be called.
               *
               * The internal queue is limited by the
               * configuration property
               * queue.buffering.max.messages */
              producer->poll(1000 /*block for max 1000ms*/);
              goto retry;
            }

        } else {
          std::cerr << "% Enqueued message (" << line.size() << " bytes) "
                    << "for topic " << topic << std::endl;
        }

    /* A producer application should continually serve
     * the delivery report queue by calling poll()
     * at frequent intervals.
     * Either put the poll call in your main loop, or in a
     * dedicated thread, or call it after every produce() call.
     * Just make sure that poll() is still called
     * during periods where you are not producing any messages
     * to make sure previously produced messages have their
     * delivery report callback served (and any other callbacks
     * you register). */
    producer->poll(0);
  }

  std::cerr << "% Flushing final messages..." << std::endl;
  producer->flush(10 * 1000 /* wait for max 10 seconds */);

  if (producer->outq_len() > 0)
    std::cerr << "% " << producer->outq_len()
              << " message(s) were not delivered" << std::endl;

  delete producer;

  return 0;
}


std::vector<std::string> str_to_vec(std::string instring, char *delimiter){
  std::vector<std::string> hostnames;
  bool flag = false;
  std::string host_name;
  for(auto &ch: instring){
    // std::cout << "Comparing " << (char)ch << " and " << *delimiter << std::endl;
    if((char)ch == *delimiter){
      flag = true;
      std::cout << host_name << "|";
      hostnames.push_back(host_name);
      host_name = "";
    } else {
      host_name.push_back(ch);
    }
  }
  hostnames.push_back(host_name);
  // if(!flag){
  //   hostnames.push_back(instring);
  // }
  // std::cout << "NO" << std::endl;
  std::cout << std::endl;
  for(auto &name: hostnames){
    std::cout << name << " and ";
  }
  std::cout << std::endl;
  return hostnames;
}



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
      std::cerr << "ERROR (" << RdKafka::err2str(event.err())
                << "): " << event.str() << std::endl;
      break;

    case RdKafka::Event::EVENT_STATS:
      std::cerr << "\"STATS\": " << event.str() << std::endl;
      break;

    case RdKafka::Event::EVENT_LOG:
      fprintf(stderr, "LOG-%i-%s: %s\n", event.severity(), event.fac().c_str(),
              event.str().c_str());
      break;

    case RdKafka::Event::EVENT_THROTTLE:
      std::cerr << "THROTTLED: " << event.throttle_time() << "ms by "
                << event.broker_name() << " id " << (int)event.broker_id()
                << std::endl;
      break;

    default:
      std::cerr << "EVENT " << event.type() << " ("
                << RdKafka::err2str(event.err()) << "): " << event.str()
                << std::endl;
      break;
    }
  }
};


void msg_consume(RdKafka::Message *message, void *opaque) {
  switch (message->err()) {
  case RdKafka::ERR__TIMED_OUT:
    break;

  case RdKafka::ERR_NO_ERROR:
    /* Real message */
    msg_cnt++;
    msg_bytes += message->len();
    if (verbosity >= 3)
      std::cerr << "Read msg at offset " << message->offset() << std::endl;
    RdKafka::MessageTimestamp ts;
    ts = message->timestamp();
    if (verbosity >= 2 &&
        ts.type != RdKafka::MessageTimestamp::MSG_TIMESTAMP_NOT_AVAILABLE) {
      std::string tsname = "?";
      if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_CREATE_TIME)
        tsname = "create time";
      else if (ts.type ==
               RdKafka::MessageTimestamp::MSG_TIMESTAMP_LOG_APPEND_TIME)
        tsname = "log append time";
      std::cout << "Timestamp: " << tsname << " " << ts.timestamp << std::endl;
    }
    if (verbosity >= 2 && message->key()) {
      std::cout << "Key: " << *message->key() << std::endl;
    }
    if (verbosity >= 1) {
      printf("%.*s\n", static_cast<int>(message->len()),
             static_cast<const char *>(message->payload()));
    }
    break;

  case RdKafka::ERR__PARTITION_EOF:
    /* Last message */
    if (exit_eof && ++eof_cnt == partition_cnt) {
      std::cerr << "%% EOF reached for all " << partition_cnt << " partition(s)"
                << std::endl;
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


class ExampleRebalanceCb : public RdKafka::RebalanceCb {
private:
  static void part_list_print(
      const std::vector<RdKafka::TopicPartition *> &partitions) {
    for (unsigned int i = 0; i < partitions.size(); i++)
      std::cerr << partitions[i]->topic() << "[" << partitions[i]->partition()
                << "], ";
    std::cerr << "\n";
  }

public:
  void rebalance_cb(RdKafka::KafkaConsumer *consumer,
                     RdKafka::ErrorCode err,
                     std::vector<RdKafka::TopicPartition *> &partitions){
     std::cerr << "RebalanceCb: " << RdKafka::err2str(err) << ": ";

     part_list_print(partitions);


    //  RdKafka::ErrorCode

     RdKafka::ErrorCode *error = NULL;
     RdKafka::ErrorCode ret_err = RdKafka::ERR_NO_ERROR;


     if (err == RdKafka::ERR__ASSIGN_PARTITIONS){
      std::cout << "ERR__ASSIGN_PARTITIONS" << std::endl;
      consumer->assign(partitions);
      //  if (consumer->rebalance_protocol() == "COOPERATIVE")
      //    error = consumer->incremental_assign(partitions);
      //  else
      //    ret_err = consumer->assign(partitions);
      //  partition_cnt += (int)partitions.size();
     }
     else{
      std::cerr << "NOT ERR__ASSIGN_PARTITIONS" << std::endl;

      //  if (consumer->rebalance_protocol() == "COOPERATIVE"){
      //    error = consumer->incremental_unassign(partitions);
      //    partition_cnt -= (int)partitions.size();
      //  }
      //  else{
      //    ret_err = consumer->unassign();
      //    partition_cnt = 0;
      //  }
     }
     eof_cnt = 0; /* FIXME: Won't work with COOPERATIVE */

    //  if (error){
    //    std::cerr << "incremental assign failed: " << error->str() << "\n";
    //    delete error;
    //  }
    //  else if (ret_err)
    //    std::cerr << "assign failed: " << RdKafka::err2str(ret_err) << "\n";
  }
};

void test_consumer(std::string brokers, std::string topic, int argc, char **argv){
  std::string error_string;
  std::string mode;
  std::string debug;
  std::vector<std::string> topics;
  bool do_conf_dump = false;
  int opt;

  // topics = str_to_vec(brokers, ",");


  RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

  ExampleRebalanceCb ex_rebalance_cb;
  conf->set("rebalance_cb", &ex_rebalance_cb, error_string);

  conf->set("enable.partition.eof", "true", error_string);

  std::cout<< "what" << std::endl;
  while ((opt = getopt(argc, argv, "g:b:z:qd:eX:AM:qv")) != -1) {
    switch (opt) {
    case 'g':
      std::cout<< "Setting group.id!" << std::endl;
      if (conf->set("group.id", optarg, error_string) != RdKafka::Conf::CONF_OK) {
        std::cerr << error_string << std::endl;
        exit(1);
      }
      break;
    case 'b':
      brokers = optarg;
      break;
    case 'z':
      std::cout<< "Setting compression.codec!" << std::endl;
      if (conf->set("compression.codec", optarg, error_string) !=
          RdKafka::Conf::CONF_OK) {
        std::cerr << error_string << std::endl;
        exit(1);
      }
      break;
    case 'e':
      exit_eof = true;
      break;
    case 'd':
      debug = optarg;
      break;
    case 'M':
      std::cout<< "Setting statistics.interval.ms!" << std::endl;
      if (conf->set("statistics.interval.ms", optarg, error_string) !=
          RdKafka::Conf::CONF_OK) {
        std::cerr << error_string << std::endl;
        exit(1);
      }
      break;
    case 'X': {
      char *name, *val;

      if (!strcmp(optarg, "dump")) {
        do_conf_dump = true;
        continue;
      }

      name = optarg;
      if (!(val = strchr(name, '='))) {
        std::cerr << "%% Expected -X property=value, not " << name << std::endl;
        exit(1);
      }

      *val = '\0';
      val++;

      RdKafka::Conf::ConfResult res = conf->set(name, val, error_string);
      if (res != RdKafka::Conf::CONF_OK) {
        std::cerr << error_string << std::endl;
        exit(1);
      }
    } break;

    case 'q':
      verbosity--;
      break;

    case 'v':
      verbosity++;
      break;

    default:
      goto usage;
    }
  }

  for (; optind < argc; optind++)
    topics.push_back(std::string(argv[optind]));

  if (topics.empty() || optind != argc) {
  usage:
    fprintf(stderr,
            "Usage: %s -g <group-id> [options] topic1 topic2..\n"
            "\n"
            "librdkafka version %s (0x%08x)\n"
            "\n"
            " Options:\n"
            "  -g <group-id>   Consumer group id\n"
            "  -b <brokers>    Broker address (localhost:9092)\n"
            "  -z <codec>      Enable compression:\n"
            "                  none|gzip|snappy\n"
            "  -e              Exit consumer when last message\n"
            "                  in partition has been received.\n"
            "  -d [facs..]     Enable debugging contexts:\n"
            "                  %s\n"
            "  -M <intervalms> Enable statistics\n"
            "  -X <prop=name>  Set arbitrary librdkafka "
            "configuration property\n"
            "                  Use '-X list' to see the full list\n"
            "                  of supported properties.\n"
            "  -q              Quiet / Decrease verbosity\n"
            "  -v              Increase verbosity\n"
            "\n"
            "\n",
            argv[0], RdKafka::version_str().c_str(), RdKafka::version(),
            RdKafka::get_debug_contexts().c_str());
    exit(1);
  }

  if (exit_eof) {
    std::string strategy;
    if (conf->get("partition.assignment.strategy", strategy) ==
            RdKafka::Conf::CONF_OK &&
        strategy == "cooperative-sticky") {
      std::cerr
          << "Error: this example has not been modified to "
          << "support -e (exit on EOF) when the partition.assignment.strategy "
          << "is set to " << strategy << ": remove -e from the command line\n";
      exit(1);
    }
  }

  /*
   * Set configuration properties
   */
  conf->set("metadata.broker.list", brokers, error_string);

  if (!debug.empty()) {
    if (conf->set("debug", debug, error_string) != RdKafka::Conf::CONF_OK) {
      std::cerr << error_string << std::endl;
      exit(1);
    }
  }

  ExampleEventCb ex_event_cb;
  conf->set("event_cb", &ex_event_cb, error_string);

  if (do_conf_dump) {
    std::list<std::string> *dump;
    dump = conf->dump();
    std::cout << "# Global config" << std::endl;

    for (std::list<std::string>::iterator it = dump->begin();
         it != dump->end();) {
      std::cout << *it << " = ";
      it++;
      std::cout << *it << std::endl;
      it++;
    }
    std::cout << std::endl;

    exit(0);
  }

  signal(SIGINT, sigterm);
  signal(SIGTERM, sigterm);


  /*
   * Consumer mode
   */

  /*
   * Create consumer using accumulated global configuration.
   */
  RdKafka::KafkaConsumer *consumer =
      RdKafka::KafkaConsumer::create(conf, error_string);
  if (!consumer) {
    std::cerr << "Failed to create consumer: " << error_string << std::endl;
    exit(1);
  }

  delete conf;

  std::cout << "% Created consumer " << consumer->name() << std::endl;

  /*
   * Subscribe to topics
   */
  RdKafka::ErrorCode err = consumer->subscribe(topics);
  if (err) {
    std::cerr << "Failed to subscribe to " << topics.size()
              << " topics: " << RdKafka::err2str(err) << std::endl;
    exit(1);
  }

  /*
   * Consume messages
   */
  while (run) {
    RdKafka::Message *msg = consumer->consume(1000);
    msg_consume(msg, NULL);
    delete msg;
  }

  #ifndef _WIN32
  alarm(10);
#endif

  /*
   * Stop consumer
   */
  consumer->close();
  delete consumer;

  std::cerr << "% Consumed " << msg_cnt << " messages (" << msg_bytes
            << " bytes)" << std::endl;

  /*
   * Wait for RdKafka to decommission.
   * This is not strictly needed (with check outq_len() above), but
   * allows RdKafka to clean up all its resources before the application
   * exits so that memory profilers such as valgrind wont complain about
   * memory leaks.
   */
  RdKafka::wait_destroyed(5000);

}


int main(int argc, char **argv){
  // if (argc != 4) {
  //     std::cerr << "Usage: " << argv[0] << " <brokers> <topic> <payload>\n";
  //     exit(1);
  // }

  // std::string brokers = argv[1];
  // std::string topic   = argv[2];
  // std::string payload   = argv[3];
  std::string brokers = "argv[1]";
  std::string topic   = "argv[2]";


  // char hostname[] = "localhost:9092";
  // char error_string[512];
  std::cout << "Hello, world!" << std::endl;
  // my_init_code();
  test_consumer(brokers, topic, argc, argv);
  // test_producer(brokers, topic, payload);
  std::cout << "Program end" << std::endl;
  return 0;
}
