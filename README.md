# Descrierea Task-ului
> ### Acest proiect implementează un joc de tip TypeRacer pe o placă Arduino Uno, utilizând un LED RGB și două butoane pentru a gestiona stările jocului.  
> ### Jocul este simplu: jucătorul trebuie să tasteze corect cuvinte afișate într-o fereastră de monitor serial într-un timp limitat.
>  
# Componentele utilizate :  
> - Arduino Uno (Placă de dezvoltare)  
> - 1x LED RGB (Pentru semnalizarea cuvintelor greșite sau corecte și pentru semnalizarea stării de idle(așteptare))  
> - 2x Butoane (Pentru start/stop rundă și pentru modificarea dificultății)  
> - 5x Rezistoare (3x 330 Ω și 2x 1k Ω)  
> - Breadboard  
> - Fire de legătura  
> 
# Detalii tehnice

> ### LED RGB - Indicator de stare:
> 
> - În starea de repaus, LED-ul va avea culoarea albă.
> - La apăsarea butonului de start, LED-ul va clipi timp de 3 secunde, indicând o numărătoare inversă până la începerea rundei.
> - În timpul unei runde: LED-ul va fi verde dacă textul introdus este corect și va deveni roșu în caz de greșeală.
> 
> ### Butonul Start/Stop:
> 
> - Modul de repaus: Dacă jocul este oprit, apăsarea butonului inițiază o nouă rundă după o numărătoare inversă de 3 secunde.
> - În timpul unei runde: Dacă runda este activă, apăsarea butonului o va opri imediat.
> 
> ### Butonul de dificultate:
> 
> - Butonul de dificultate controlează viteza cu care apar cuvintele și poate fi folosit doar în starea de repaus.
> - La fiecare apăsare, dificultatea se schimbă ciclind între: (Easy, Medium, Hard).
> - La schimbarea dificultății, se trimite un mesaj prin serial: “Easy/Medium/Hard mode on!”.
> 
> ### Generarea cuvintelor:
> 
> - Se va crea un dicționar de cuvinte.
> - În timpul unei runde, cuvintele vor fi afișate în terminal într-o ordine aleatorie.
> -Dacă cuvântul curent a fost scris corect, un cuvânt nou va fi afișat imediat. Dacă nu, un nou cuvânt va apărea după intervalul de timp stabilit în funcție de dificultate.
> 
> ### Alte observații:
> 
> - Timpul alocat pentru o rundă este de 30 de secunde.
> - La sfârșitul fiecărei runde, se va afișa în terminal câte cuvinte au fost scrise corect.

# Flow

> - Jocul este în repaus. LED-ul RGB are culoarea albă.
> 
> - Se alege dificultatea jocului folosind butonul de dificultate, iar în terminal va apărea “Easy/Medium/Hard mode on!”.
> 
> - Se apasă butonul de start/stop.
> 
> - LED-ul clipește timp de 3 secunde, iar în terminal se va afișa numărătoarea înversă: 3, 2, 1.
> 
> - LED-ul devine verde și încep să apară cuvinte de tastat.
> 
> - La tastarea corectă, următorul cuvânt apare imediat. Dacă nu se tasteaza cuvântul în timpul stabilit de dificultate, va apărea un nou cuvânt.
> 
> - O greșeală face LED-ul să devină roșu. Pentru a corecta cuvântul, se va folosi tasta BackSpace.
> 
> - Dupa 30 de secunde, runda se termină, iar în terminal se va afișa scorul: numărul total de cuvinte scrise corect.
> 
> - Jocul se poate opri oricând cu butonul de start/stop. 
# Poze ale set-up-ului fizic
> ![Poză 1](Pictures/Pic_1_Setup%20(1).jpeg)
> ![Poză 2](Pictures/Pic_1_Setup%20(2).jpeg)
> ![Poză 3](Pictures/Pic_1_Setup%20(3).jpeg)
> ![Poză 4](Pictures/Pic_1_Setup%20(4).jpeg)
>
# Schema electrică în Wokwi
> ![Schema electriă](Pictures/schema_electrica.png)
# Funcționalitatea montajului fizic

[![Funcționalitate 2](https://img.youtube.com/vi/kHTQRHOxb44/0.jpg)](https://www.youtube.com/watch?v=kHTQRHOxb44)
[![Funcționalitate 1](https://img.youtube.com/vi/QHV0p64hw3Y/0.jpg)](https://www.youtube.com/watch?v=QHV0p64hw3Y)