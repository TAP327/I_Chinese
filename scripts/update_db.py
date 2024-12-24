"""
Simple python script for updating the i_chinese.db SQLite DB.

usage: UpdateDB [-h] --table {word,sentence} --file FILE

Update SQLite DB with new entries

options:
  -h, --help            show this help message and exit
  --table {word,sentence}
                        The name of the table to update. Choose either 'word' or 'sentence'.
  --file FILE           The JSON file containing the data to insert.

Note: This will only update the DB not overwrite it. Ensure that your update_file
is new content to avoid duplication. 
"""

import json
import sqlite3
import argparse


def update_db(table: str, update_file: str) -> None:
    with open(update_file, 'r') as file:
        json_data = json.load(file)

    conn = sqlite3.connect('../assets/i_chinese.db')
    cursor = conn.cursor()

    if table == 'word':
        sql_statement = '''
            INSERT INTO word (id, chinese, pinyin, definition, level, sentences)
            VALUES (:id, :chinese, :pinyin, :definition, :level, :sentences)
        '''
    elif table == 'sentence':
        sql_statement = f'''
            INSERT INTO word (id, chinese, pinyin, english)
            VALUES (:id, :chinese, :pinyin, :english)
        '''

    for entry in json_data:
        try:
            cursor.execute(sql_statement, entry)
        except sqlite3.IntegrityError as e:
            # Handle duplicate entries gracefully
            print(f"Skipping duplicate entry with id {entry['id']}")


    conn.commit()
    conn.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="UpdateDB",
        description="Update SQLite DB with new entries",
    )
    parser.add_argument(
        '--table',
        type=str,
        choices=['word', 'sentence'],  # Add valid table names here
        required=True,
        help="The name of the table to update. Choose either 'word' or 'sentence'."
    )
    parser.add_argument(
        '--file',
        type=str,
        required=True,
        help="The JSON file containing the data to insert."
    )
    args = parser.parse_args()

    update_db(table=args.table, update_file=args.file)