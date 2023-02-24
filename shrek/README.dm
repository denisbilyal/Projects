Шрек 2023


Магарето и Шрек тръгват на приключение в София, обаче Магарето било гладно… Тръгнали на път към най-хубавите дюнери, като пътешком спечелили раздаване на билети за концерт. Въпреки все още неизвестните позиция и време на този спиращ дъха спектакъл, те са убедени, че сцената е много голяма. Явно никога не са били в България и за това са сигурни, че цялата сцена ще бъде построена без да има безследно изчезнали части, но все пак те имат цял екип за построяването ѝ, преди пристигането си на позиция Х.

С течение на ремонтните дейности се оказало, че ръководителят на екипа по

осветлението на сцената е бил привикан от група общи работници, размахващи малка

бутилка от кока кола с капачка от фанта и надраскан с черен маркер надпис -

“скоросмъртница”. Този вълшебен еликсир довел ръководителя до състояние негодно

за работа с техниката, управляваща осветителните тела по сцената. За жалост той

бил единственият разбиращ от така известния протокол DMX 512, с помощта на който

се управлява от конзолата разпределението на сигналите по кабелите, отиващи към

осветителните тела. Магарето и Шрек моментално били уведомени за този инцидент. Те проучили за подходящи специалисти в България и открили, че в ИС има студенти, които могат да помогнат. Като за начало, студентите трябвало да се

запознаят как работи DMX 512, но опростен вариант на системата, защото нямат много време до концерта.

 Представете си лента дълга 512 разделения. Всяко разделение се нарича канал. През тези канали преминава информация за осветителното тяло на сцената. Примерно в каква посока да се завърти някой прожектор и/или с какъв цвят светлина да свети. Понеже прожекторите са сложна техника, не могат да се управляват само през един канал и за това им трябват няколко последователни канала. В зависимост от модела на осветителното тяло те може да са различен брой. За да работи системата за управление трябва да се определи на кои канали да се сложат различните прожектори. Те може да са примерно: един на канали [1:10] и втори на - [11:20]. Така системата знае, без объркване, на кой канал да подаде сигнал който да се достави правилно до прожектора. Такива канали ще са в състояние - good.

Понякога обаче може да искаме два или повече прожектора да се движат и светят по

един и същи начин, за това и ги слагаме на един и същ интервал от канали, за да не

се заемат излишно каналите. Такова състояние ще наричаме duplicate. Понякога се

получават и обърквания в системата и каналите на два прожектора се пресичат, но не

напълно. Примерно един е на канали в интервал [1:10], а друг е на канали [5:17]. Така

каналите [5:10] ще са конфликтни, защото по тях се изпращат конфликтни сигнали.

Тези състояния ще наричаме conflict. Останалите в интервалите [1:4] и [11:17] си

остават в състояние good, ако нямат конфликти с каналите на някой друг прожектор.


Задачата, която трябва да решат студентите от ИС ще наречем DMX Patching. Тази

система ще приема последователност от заявки:


- добавяне на прожектор, което става с командата

a <serial-number> <number-of-channels> <start-channel>

където:

● а е символа 'а'.

● <serial-number> определя серийния номер на прожектора както следва:

- serial-number е положително цяло число, не по-голямо от 216

.

- serial-number е уникално число на прожектора, за това, ако се опитате да добавите в системата прожектор със сериен номер, който вече

съществува, трябва системата да не ви позволи и добавянето да не бъде успешно!

● <number-of-channels> определя броя на каналите, които използва този прожектор - цяло число;

● <start-channel> определя номера на първия канал по който се управлява

прожектора.

Трябва да проверявате дали заявката е валидна (целият интервал от канали трябва

да е между 1 и 512).


Също така Магарето и Шрек не искат фалшиви прожектори да им светят по сцената.

Затова системата трябва да не добавя такива. Фалшиви прожектори са такива, за

които серийният номер не се дели на броя вдигнати битове на самия сериен номер.

Тъй като системата е все още в бета версия за сега не може да поддържа повече от

64 прожектора. Уверете се, че няма да превишите това количество, като добавяне на

прожектор става само след като са изпълнени горните условия И добавените за

сега прожектори са < 64.


- махане на прожектор. Извършва се с командата: r <serial-number>.

Ако прожектор с такъв сериен номер не съществува, това трябва да се съобщи на

потребителя с подходящо съобщение на стандартния изход и командата за

премахване да бъде прекратена.


- преместване на вече съществуващ прожектор:

m <serial-channel> <new-start-interval>


Ако преместването на интервала води до излизането му от края на каналната лента

и/или няма прожектор с такъв сериен номер, командата трябва да прекрати

изпълнението си и да изпише подходящо съобщение.


- принтиране на текущата схема на каналите, става с командата р

Полетата, трябва добре да уведомяват потребителя на коя позиция какво е

състоянието на канала:

Примерни символи за всяко състояние (можете да си изберете други)

- empty - ‘_’

- good - ‘o’

- duplicate - ‘+’

- conflict - ‘x’


- излизане от системата, с командата: е

========


Примерно изпълнение на програмата:


Enter new command: a 10 10 50

Enter new command: a 20 10 70

Enter new command: a 40 15 150

Enter new command: a 80 15 150

Enter new command: a 160 8 200

Enter new command: a 320 15 215

Enter new command: a 640 15 204

Enter new command: p

__________________________________________________
oooooooooo__________oooooooooo____________________
__________________________________________________
+++++++++++++++___________________________________
ooooxxxxoooooooxxxxooooooooooo____________________
__________________________________________________
__________________________________________________
__________________________________________________
__________________________________________________
__________________________________________________
____________



Enter new command: m 40 180

Enter new command: p

__________________________________________________
oooooooooo__________oooooooooo____________________
__________________________________________________
ooooooooooooooo______________ooooooooooooooo______
ooooxxxxoooooooxxxxooooooooooo____________________
__________________________________________________
__________________________________________________
__________________________________________________
__________________________________________________
__________________________________________________
____________



Enter new command: r 640

Enter new command: p

__________________________________________________
oooooooooo__________oooooooooo____________________
__________________________________________________
ooooooooooooooo_______________ooooooooooooooo_____
oooooooo_______ooooooooooooooo____________________
__________________________________________________
__________________________________________________
__________________________________________________
__________________________________________________
__________________________________________________
____________
