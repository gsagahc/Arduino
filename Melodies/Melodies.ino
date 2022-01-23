#include <Pitches.h> //add Equivalent frequency for musical note
#include <themes.h> //add Note vale and duration 


int botao;

void Play_Pirates()
{ 
  for (int thisNote = 0; thisNote < (sizeof(Pirates_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Pirates_duration[thisNote];//convert duration to time delay
    tone(8, Pirates_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.05; //Here 1.05 is tempo, increase to play it slower
    delay(pauseBetweenNotes);
    noTone(8); //stop music on pin 8 
    }
}

void Play_CrazyFrog()
{
  for (int thisNote = 0; thisNote < (sizeof(CrazyFrog_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / CrazyFrog_duration[thisNote]; //convert duration to time delay
    tone(8, CrazyFrog_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;//Here 1.30 is tempo, decrease to play it faster
    delay(pauseBetweenNotes);
    noTone(8); //stop music on pin 8 
    }
}

void Play_MarioUW()
{
    for (int thisNote = 0; thisNote < (sizeof(MarioUW_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / MarioUW_duration[thisNote];//convert duration to time delay
    tone(8, MarioUW_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.80;
    delay(pauseBetweenNotes);
    noTone(8); //stop music on pin 8 
    }
}

void Play_Titanic()
{
    for (int thisNote = 0; thisNote < (sizeof(Titanic_note)/sizeof(int)); thisNote++) {

    int noteDuration = 1000 / Titanic_duration[thisNote];//convert duration to time delay
    tone(8, Titanic_note[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 2.70;
    delay(pauseBetweenNotes);
    noTone(8); //stop music on pin 8 
    }
}
void play_happy(){
  // iterate over the notes of the melody:
for (int thisNote = 0; thisNote <27 ; thisNote++) {

// to calculate the note duration, take one second 
// divided by the note type.
//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 1000/noteDurations[thisNote];
 tone(8, melody[thisNote],noteDuration);

// to distinguish the notes, set a minimum time between them.
// the note’s duration + 30% seems to work well:
 int pauseBetweenNotes = noteDuration * 1.30;
 delay(pauseBetweenNotes);
 // stop the tone playing:
  noTone(8);
 }
}
void wish_melodia(){
  int size = sizeof(wish_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / wish_tempo[thisNote];

      tone(8, wish_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      tone(8, 0, noteDuration);

    }
}
void santa_claus(){
  int size = sizeof(santa_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 900 / santa_tempo[thisNote];

      tone(8, santa_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      tone(8, 0, noteDuration);

    }
}

void bells(){
   int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / bells_tempo[thisNote];

      tone(8, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      tone(8, 0, noteDuration);

    }
  }


void setup() {
botao=0;
Serial.begin(9600);
}

void loop() {
  /*   Play_Pirates(); 
     delay(1000);
     for (int i=0; i=4; i++){
     Play_CrazyFrog();  
     delay(100);
     }
     delay(1000);
     Play_MarioUW();  
     delay(1000);
     play_happy();
     delay(1000);
     Play_Titanic();
     delay(1000);*/
    for (int i=0; i<=4; i++){
     wish_melodia();
    }
     delay(1000);

    for (int i=0; i<=4; i++){
     santa_claus();
     delay(1000);
    }
    for (int i=0; i<=5; i++){
      bells();
      delay(1000);
    }
}
