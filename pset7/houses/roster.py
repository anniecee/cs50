import sys
import csv
import cs50

# Error message for incorrect number of command lines
if len(sys.argv) != 2:
    print("Error! Usage: python roster.py name_of_house(Gryffindor, Slytherin, Ravenclaw, Hufflepuff")
    exit(1)
    
#Set up database connection
db = cs50.SQL("sqlite:///students.db")

#Select rows from table using db.execute & save in a list of dict named "student_list"
student_list = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", sys.argv[1])

#Loop through each ith element of the student list
for i in range(len(student_list)):
    #Print name for student with no middle name
    if student_list[i]['middle'] == None:
        print(f"{student_list[i]['first']} {student_list[i]['last']}, born {student_list[i]['birth']}")
    #Print name for student with middle name
    if student_list[i]['middle'] != None:
        print(f"{student_list[i]['first']} {student_list[i]['middle']} {student_list[i]['last']}, born {student_list[i]['birth']}")