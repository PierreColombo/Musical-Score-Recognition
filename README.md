# Personnal-Projects

##Traitement d'une partition

### Introduction
Development of a Musical Recognition software in Matlab and C++ able to extract the musical data out of any kind of picture of a musical score. Signal and Image Processing techniques were widely used to isolate symbols, and Machine Learningand Statistics were used to differentiate between different symbol types.

### Our Strategy 
Example on this score :
![imagedebase](https://cloud.githubusercontent.com/assets/22492839/20073374/4a06019a-a52c-11e6-9a69-3666511e7969.jpg)
To achieve our goal we do the following steps : 

#### Pre-processing the score
- if there exists a bias we apply a rotation to the picture to make it perfectly horizontal (Done using a convolution product between two halfs of the picture )
- we get the lines of the musical score by summing all the lines of matrix the score

![detection des lignes](https://cloud.githubusercontent.com/assets/22492839/20073620/345def32-a52d-11e6-9b20-66a258fd335b.jpg)

- we get the line thickness and the line spacing by using histograms

#### Spliting the score into sub-score
- by using geometrical considerations we split the score into sub-score
![sousimage1](https://cloud.githubusercontent.com/assets/22492839/20073400/6e413f5c-a52c-11e6-9ae3-a7e6d247f83e.jpg)
![sousimage2](https://cloud.githubusercontent.com/assets/22492839/20073730/b21bc6b0-a52d-11e6-91d6-b9bfaae67971.jpg)
![sousimage3](https://cloud.githubusercontent.com/assets/22492839/20073758/c503f810-a52d-11e6-8293-f887af023504.jpg)

- we substract carrefully the lines to the score to avoid noise in our recognition


![sousimage1 sans porte](https://cloud.githubusercontent.com/assets/22492839/20073399/6e40e502-a52c-11e6-859d-c92d120bf63c.jpg)

#### Isolating into box every single symbol
- we use growth algorithms with origin the queue of the note to put every note into box

![resultat](https://cloud.githubusercontent.com/assets/22492839/20073398/6e401fd2-a52c-11e6-99b0-0f1ccb221589.png)


#### Getting the note value & the rythm
- with template matching applied in every box we decide if said box is a quaver, a semiquaver etc.... and get the pitch : (C,D,E etc...)

### Conclusion : Results
Our algorithm is quite efficient on standard scores (like you have in the folder), to improve it we can give several ideas :
- use a neural network to get better accuracy, moreover template matching is very sensitive to the high variability of the symbols...
- continue to define new responsives templates to discover all "classical symbols".
