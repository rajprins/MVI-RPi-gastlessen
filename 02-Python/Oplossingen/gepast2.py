bedrag = int(input("Geef bedrag op in centen (tussen 0 en 500): "))
beschikbareMunten = (200, 100, 50, 20, 10, 5, 2, 1)

print("Het bedrag van %i Eurocent kan met deze munten worden betaald:" %bedrag)
# Definieer een verzameling muntwaardes en loop hier doorheen.
for munt in beschikbareMunten :
    aantal = 0

    #Doe dit zo lang bedrag groter is dan gekozen munt
    while (bedrag >= munt) :
        aantal = aantal + 1     #Verhoog aantal gebruikte munten van een waarde
        bedrag = bedrag - munt  #Verminder restbedrag met de waarde van de munt

    if (aantal > 0) :
        print(aantal, 'x', munt)