# Personnal-Projects

##Traitement d'une partition

### Introduction
You would like to transpose your musical score? It takes time a lot of time. We have developed an algorithm in C++ to do it. With this algorithm and a simple picture of the musical score, our algorithm recognizes the notes and the rythms of the score. 

### Our Strategy 
To perform our action we do the following steps : 

#### Pre-processing the score
- if there exist a biais we apply a rotation to the picture to have it horizontally ( we use a convolution product between two part of the picture with a fft in butterfly to do that)
- we get the lines of the musical score by summing all the lines of matrix the score
- we get the line Thickness and the line spacing by using histograms

#### Spliting the score into sub-score
- by using geometrical considerations we split the score into sub-score

#### Isolating into box every single notes
- we use growing algorithms with origin :the queue of the note to put every note into box

#### Getting the note value & the rythm
- with template matching applied in every box we decide if this is a quaver, a semiquaver etc.... and get the pitch : if(C,D,E etc...)

### Conclusion : Results
Our algorithm is quite efficient on easy score (like you have in the folder), to improve if you could :
- use a neuronal network to get better accuracy, moreover template matching is very sensitive to the high variability of the symbols...
- continue to define new responsives templates to discover all th "classical symbols".
