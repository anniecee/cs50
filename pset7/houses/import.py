import sys
import csv
import cs50

# Error message for incorrect number of command lines
if len(sys.argv) != 2:
    print("Error! Usage: python import.py characters.csv")
    exit(1)

#Set up database connection
db = cs50.SQL("sqlite:///students.db")

#Open csv file to read
with open(sys.argv[1], "r") as input_file:
    #Create reader object to iterate over lines in the input_file
    dict_reader = csv.DictReader(input_file)
    
    #Initiate id number
    id_number = 0
    
    #Loop through the file row by row
    for row in dict_reader:
        #Increment id number for each student added
        id_number += 1
        
        #Separate full name into first, middle and last name
        #Case 1: Only first and last name
        if len(str.split(row['name'])) == 2:
            full_name = str.split(row['name'])
            first_name = full_name[0]
            middle_name = None
            last_name = full_name[1]
        #Case 2: First, middle and last name
        if len(str.split(row['name'])) == 3:
            full_name = str.split(row['name'])
            first_name = full_name[0]
            middle_name = full_name[1]
            last_name = full_name[2]
            
        #Declare house and birth year to save later
        house = row['house']
        birth = int(row['birth'])
        
        #Insert information into students.db database by executing SQL queries
        db.execute("INSERT INTO students (id, first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?, ?)", id_number, first_name, middle_name, last_name, house, birth)
        