#!/usr/bin/python3
import mysql.connector
from mysql.connector import errorcode
import logging

logging.basicConfig(
        filename='railApplication.log',
        format='%(asctime)s.%(msecs)-3d:%(filename)s:%(funcName)s:%(levelname)s:%(lineno)d:%(message)s',
        datefmt='%Y-%m-%d %H:%M:%S',
        level=logging.INFO
    )


class insufficientDataError(Exception):
    """Called when there is insufficient data passed to the class"""
    def __init__(self):
        self.showError()
        return

    def showError(self):
        print("Insifficient data passed")

class mysqlConnector():
    """
    This class is used to connect to the mysql database and peform basic mysql processes.
    It supports only where condition as of now
    """
    def __init__(self,**kwargs):
        keys = kwargs.keys()
        try:
            if(set(["password","host","user","database"]).issubset(keys)):
                self.host = kwargs["host"]
                self.user = kwargs["user"]
                self.password = kwargs["password"]
                self.database = kwargs["database"]
            elif(set(["passwd","host","user","database"]).issubset(keys)):
                self.host = kwargs["host"]
                self.user = kwargs["user"]
                self.password = kwargs["passwd"]
                self.database = kwargs["database"]
            elif(set(["connection"]).issubset(keys)):
                logging.info("Trying to connect to the database")
                self.mysqlConnection = kwargs["connection"]
                self.cursor = self.mysqlConnection.cursor(dictionary=True)
                logging.info("Connection successful")
            else:
                raise insufficientDataError()
        except insufficientDataError:
            exit(0)
        except:
            print("Uncaught error in constructor of mysqlConnector class.")
            exit(0)

    def showData(self):
        print(self.host)
        print(self.user)
        print(self.password)
        print(self.database)

    def setConnection(self):
        try:
            logging.info("Trying to connect to the database")
            self.mysqlConnection = mysql.connector.connect(
            	host		=	self.host,
            	user		=	self.user,
            	passwd		=	self.password,
            	database	=	self.database
            )
            self.cursor = self.mysqlConnection.cursor(dictionary=True)
            logging.info("Connection successful")
            return self.cursor
        except mysql.connector.Error as err:
            logging.critical("Mysql connector error Error No:%4d:%s" % (err.errno,str(err.msg)))
            if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
            	logging.critical("Access was denied.")
            elif err.errno == errorcode.ER_BAD_DB_ERROR:
            	logging.critical("Database does not exist.")
            elif err.errno == errorcode.ER_BAD_FIELD_ERROR:
            	logging.critical("Invalid field.")
            elif err.errno == errorcode.ER_BAD_TABLE_ERROR:
            	logging.critical("Table does not exist.")
            else:
            	logging.critical(str(err.msg))
            print("Error while connecting to he database, check the logs!")
            exit(0)

    def insert(self,tableName,insDict):
        logging.info("Generating CREATE query(%s) ..." % (tableName))
        finalQuery = ("INSERT INTO %s(" % (tableName))
        key = list(insDict.keys())
        value = list(insDict.values())
        length = len(key)
        finalQuery = finalQuery + "`" + key[0] + "`"
        for index in range(length - 1):
            finalQuery = finalQuery + "," + "`" + key[index + 1] + "`"
        finalQuery = finalQuery + ") VALUES("
        finalQuery = finalQuery + "'" + str(value[0]) + "'"
        for index in range(length - 1):
            if(value[index + 1] == "null"): #THE BLOCK BELOW GENEREATES ",null"
                finalQuery = finalQuery + "," + str(value[index + 1])
                continue
            finalQuery = finalQuery + "," + "'" + str(value[index + 1]).replace("'",r"\'") + "'" #THE BLOCK BELOW GENEREATES ",'val'"
        finalQuery = finalQuery + ");"
        logging.debug(finalQuery)
        self.cursor.execute(finalQuery)

    def delete(self,tableName,delDict,whereDict):
        logging.info("Generating DELETE query(%s) ..." % (tableName))
        finalQuery = ("DELETE FROM " + tableName + " WHERE ")
        key = list(whereDict.keys())
        value = list(whereDict.values())
        length = len(key)
        finalQuery = finalQuery + key[0] + "=" + "'" + str(value[0]) + "'"
        for index in range(length - 1):
            finalQuery = finalQuery + " AND " + key[index + 1] + "=" + "'" + str(value[index + 1]) + "'"
        finalQuery = finalQuery + ";"
        logging.debug(finalQuery)
        self.cursor.execute(finalQuery)

    def update(self,tableName,setDict,whereDict):
        logging.info("Generating UPDATE query(%s) ..." % (tableName))
        finalQuery = ("UPDATE %s SET " % (tableName))
        key = list(setDict.keys())
        value = list(setDict.values())
        length = len(key)
        finalQuery = finalQuery + key[0] + "=" + "'" + value[0] + "'"
        for index in range(length - 1):
            finalQuery = finalQuery + "," + key[index + 1] + "=" + "'" + value[index + 1] + "'"
        finalQuery = finalQuery + " WHERE "
        key = list(whereDict.keys())
        value = list(whereDict.values())
        length = len(key)
        finalQuery = finalQuery + key[0] + "=" + "'" + value[0] + "'"
        for index in range(length - 1):
            if(value[index + 1].upper()	 == "NULL"):
                finalQuery = finalQuery + " AND " + key[index + 1] + " IS NULL"
                continue
            finalQuery = finalQuery + " AND " + key[index + 1] + "=" + "'" + value[index + 1] + "'"
        finalQuery = finalQuery + ";"
        logging.debug(finalQuery)
        self.cursor.execute(finalQuery)

    def select(self,tableName,dataList,whereDict = None):
        logging.info("Generating SELECT query(%s)" % (tableName))
        finalQuery = ("SELECT `" + dataList[0] + "`")
        length = len(dataList)
        for index in range(length - 1):
            finalQuery = finalQuery + ",`" + dataList[index + 1] + "`"
        finalQuery = finalQuery + " FROM " + tableName
        if(whereDict != None):
            finalQuery = finalQuery + " WHERE "
            key = list(whereDict.keys())
            length = len(key)
            finalQuery = finalQuery + key[0] + "=" + "'" + whereDict[key[0]] + "'"
            for index in range((length - 1)):
                finalQuery = finalQuery + " AND " + key[index + 1] + "=" + "'" + whereDict[key[index + 1]] + "'"
            finalQuery = finalQuery + ";"
        self.cursor.execute(finalQuery)
        response = self.cursor.fetchall()
        logging.debug(response)
        return response

    def closeConnection_(self):
        self.mysqlConnection.closeConnection()
        pass



if __name__ == "__main__":
    print("No point running this!")
else:
    pass
