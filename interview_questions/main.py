#!/usr/bin/python3
"""
LBRACE : {
RBRACE : }

LPARENS : (
RPARENS: )

NAME : [a-z]+
NUMBER : [0-9]+

DECL : val NAME = NUMBER
COND : (NAME | NUMBER) (> | < | >= | <= | == | !=) (NAME | NUMBER)
FNCALL : NAME LPARENS (NAME | NUMBER)* RPARENS

STATEMENT: DECL | IF | FN

IF : if COND LBRACE STATEMENT* RBRACE
"""

import tokenize as tk
from io import BytesIO


def read_file(fname="./code.txt"):
    with open(fname, "r") as fl:
        return fl.read()


# def process():
#     data = tk.tokenize(BytesIO(read_file().encode("utf-8")).readline)
#     encoding_info = next(data)
#     for tok in data:
#         print(tk.tok_name[tok.type], tok.string)

def process():
    with open("./code.txt", "r") as fl:
        data = tk.generate_tokens(fl.readline)
        for tok in data:
            print(tk.tok_name[tok.type], tok.string)


# Main function
if __name__ == "__main__":
    process()

