bedrag = float(input("Geef bedrag tussen 0.00 en 5.00 euro: "))
beschikbareMunten = (2.00, 1.00, 0.50, 0.20, 0.10, 0.05, 0.02, 0.01)
restbedrag = bedrag

print("Het bedrag van %i Euro kan met deze munten worden betaald:" %bedrag)

# Loop door verzameling munten
for munt in beschikbareMunten :
    aantal = restbedrag // munt  # Hoe vaak past munt in bedrag?
    restbedrag = restbedrag % munt

    if aantal > 0 :
        print("%i x %1.2f" % (aantal, munt))