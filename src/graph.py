import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("/Users/danilakokin/Desktop/result.csv")

fig = plt.figure()
ax = plt.axes()
ax.plot('length', 'GradeSchool', data = df, label = "GradeSchool", color='blue')
ax.plot('length', 'Karatsuba', data = df, label = "Karatsuba", color='purple')
ax.plot('length', 'Divivde&Conquer', data = df, label = "Divide & Conquere", color='red')

plt.title("Algorithm trends")
plt.xlabel("Number of Digits")
plt.ylabel("Seconds")

plt.legend()
plt.show()
