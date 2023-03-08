import random

czas = 15000000
lista= ["qTemperature","qHumidity","qLight","qOxygenation","qCarbonDioxide"]


with open('infile.txt', 'w') as f:
    for i in range(200):
        
        los = random.randint(0, 1023)
        f.write(': '+str(czas)+", "+str(lista[random.randint(0, len(lista) - 1)])+", "+str(los)+'\n')
        czas = czas + 10000000

def print_hi(name):
    print(f'Hi, {name}')

if __name__ == '__main__':
    print_hi('PyCharm')