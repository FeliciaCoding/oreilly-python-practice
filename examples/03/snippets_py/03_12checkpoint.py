## 3.12 Program Development: Sentinel-Controlled Iteration

### Checkpoint 1 Snippets

### Checkpoint 2 Snippets

### Checkpoint 3 Snippets

# AverageTemperature.py — Fahrenheit average calculator with sentinel value 999
total = 0
counter = 0

while tmp := int(input("enter integer Fahrenheit temperatures between -212 to 212 included : ")):
    if tmp == 999:
        break
    elif tmp < -212 or tmp > 212:
        print("invalid range, please choose the range between -212 to 212 included! ")
    else: 
        total += tmp 
        counter += 1
        print (f"temperature : {tmp}, counter : {counter}, total : {total} ")

# display avg 

if counter > 0 : 
    print( f" avage temperate : {total} / {counter} = {total/counter:.2f}")
else: 
    print("No termp entered!\nquite program")

##########################################################################
# (C) Copyright 1992-2026 by Deitel & Associates, Inc. and               #
# Pearson Education, Inc. All Rights Reserved.                           #
#                                                                        #
# DISCLAIMER: The authors and publisher of this book have used their     #
# best efforts in preparing the book. These efforts include the          #
# development, research, and testing of the theories and programs        #
# to determine their effectiveness. The authors and publisher make       #
# no warranty of any kind, expressed or implied, with regard to these    #
# programs or to the documentation contained in these books. The authors #
# and publisher shall not be liable in any event for incidental or       #
# consequential damages in connection with, or arising out of, the       #
# furnishing, performance, or use of these programs.                     #
##########################################################################
