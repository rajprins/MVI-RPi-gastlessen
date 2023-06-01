bedrag = float(input("Geef bedrag tussen 0.00 en 5.00 Euro: "))
beschikbareMunten = (2.00, 1.00, 0.50, 0.20, 0.10, 0.05, 0.02, 0.01)
totaalAantal = 0

print("Het bedrag van %i Euro kan met deze munten worden betaald:" %bedrag)

# Definieer een verzameling muntwaardes en loop hier doorheen.
for munt in beschikbareMunten :
    aantal = 0

    #Doe dit zo lang bedrag groter is dan gekozen munt
    while (bedrag >= munt) :
        aantal += 1             #Verhoog aantal gebruikte munten van een waarde
        totaalAantal += 1       #Verhoog totaal aantal gebruikte munten
        bedrag = bedrag - munt  #Verminder restbedrag met de waarde van de munt

    if (aantal > 0) :
        print("%i x %1.2f" % (aantal, munt))

print("------------------------------")
print("Aantal munten: %i" %totaalAantal)