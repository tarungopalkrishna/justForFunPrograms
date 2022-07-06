import sys
from os import environ, rename
from os import path
from os import listdir
from pymongo import MongoClient
import pandas as pd
import json
# from bson.json_util import
import re

def read_secrets(fl_name="./.secrets.json"):
    with open(fl_name) as f:
        secrets = json.load(f)
        return secrets


try:
    MONGO_URI=environ["MONGO_URI"]
except KeyError:
    MONGO_URI=read_secrets()["MONGO_URI"]

def get_connection(database_name, collection_name):
    global MONGO_URI
    conn = MongoClient(MONGO_URI)
    coll_conn = conn[database_name][collection_name]
    return coll_conn

def upload():
    pass

def dataframe_to_dict(dataframe):
    return dataframe.to_dict(orient='records')

def dataframe_to_json(dataframe):
    return dataframe.to_json(orient='records')

def datafram_to_bson(dataframe):
    pass


PATTERN = re.compile('[^a-z0-9!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~\\\\ ]+', re.IGNORECASE)

def rename_column_names(dict_list):
    # print(dict_list)
    def sub_symbols(symb):
        symb = symb.replace("%","per")
        symb = symb.replace(" ","_")
        return symb.strip()
    def filter_string(instring):
        """
        This method accepts a string and removes all non-alphanumeric characters and
        non-punctuation characters.
        """
        global PATTERN
        return re.sub(PATTERN, ' ', instring).strip()
    def preprocess_string(instring):
        instring = instring.strip()
        instring = sub_symbols(instring)
        instring = filter_string(instring)
        return instring
    mapping = {dt: preprocess_string(dt.lower()) for dt in dict_list}
    return mapping


def upload_to_mongo(file_name, database_name, collection_name):
    connection = get_connection(database_name, collection_name)
    if(file_name.endswith(".xlsx")):
        df = pd.read_excel(file_name)
        # print(dataframe_to_dict(df))
        new_columns = rename_column_names(df.columns)
        df.rename(columns=new_columns,inplace=True)
        for record in dataframe_to_dict(df):
            print(record)
            connection.insert_one(record)
    elif(file_name.endswith(".csv")):
        df = pd.read_csv(file_name)
    elif(path.isdir(file_name)):
        files = listdir(file_name)
        for file in files:
            if(file.endswith(".xlsx")):
                df = pd.read_excel(path.join(file_name, file))
            elif(file.endswith(".csv")):
                df = pd.read_csv(path.join(file_name, file))
    else:
        print("file_name argument must be a file or directory")
        sys.exit(0)


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print('Usage: upload.py <database_name> <collection_name> <file_name>')
        sys.exit(1)
    upload_to_mongo(sys.argv[3], sys.argv[1], sys.argv[2])