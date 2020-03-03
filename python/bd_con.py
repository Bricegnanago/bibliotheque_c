# import mysql.connector

# mydb = mysql.connector.connect(
#   host="localhost",
#   user="root",
#   passwd="root",
#   database="testdb"
# )
# #virtualenv -p python3 sqlenv


# mycursor = mydb.cursor()

# mycursor.execute("SELECT * FROM Book")

# myresult = mycursor.fetchall()

# for x in myresult:
#   print(x)
import matplotlib.pyplot as plt
name = ['-18', '18-25', '25-50', '50+']
data = [5000, 26000, 21400, 12000]

explode=(0, 0.15, 0, 0)
plt.pie(data, explode=explode, labels=name, autopct='%1.1f%%', startangle=90, shadow=True)
plt.axis('equal')
plt.show()
