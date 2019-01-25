/*
 * Reverie Language Technology
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#define REVERIE_OK        0
#define REVERIE_ERROR    -1

/*Reverie Language Constants*/
typedef enum languageindex
{
    Hindi,
    Assamese,
    Bengali,
    Gujarati,
    Marathi,
    Telugu,
    Tamil,
    Malayalam,
    Punjabi,
    Odia,
    Kannada,
    Urdu,
    Kashmiri,
    English,
	Nepali,
	Konkani,
	Maithili,
	Dogri,
	Sindhi,
	Sanskrit,
	Manipuri,
	Bodo,
	Santali

} LanguageIndex;


/**
* This method sets the language for the R9 library.
*
* @param language(IN)The language index of the language to be set.
* @param Status	(OUT)The success/error status.
*
* @return void
*/
void reverieSetLanguage(LanguageIndex language,int *Status);


/*This fun return list of character bind to a particular key for multitap..*/

void getReverieCharListMulti_tap(int keyCode,unsigned short charList[21][5],int* count,
        unsigned short prevUnichar, int *Status);

/*This fun return the keyList for a particular key for R9*/

void getReverieCharList(int keyCode,unsigned short charList[21][5],int* count,
        unsigned short prevUnichar, int *Status);

/*This fun returns the period(viram for Indian languages) for particular language*/
unsigned short getReveriePeriodChar(LanguageIndex language);



/**
 * Sets if half words are to be returned by R9 library.
 *
 * @param isHalf(IN)isHalf is 0 is only full words are to be
 * returned and 1 is half words is to be returned.
 *
 * @return void
 *
 */
void reverieSetHalfWord(char isHalf);



/**
 * Returns the predicted words for the keycode Sequence for the set language.
 *
 * @paramkeycodeSeq(IN)The number sequence for which words are to be predicted.
 * @param words(OUT) The predicted words. It is assumed that at max 30
 * words will be returned. A word cannot be more than length 30.
 * @param numberOfWords(OUT)The number of words returned.
 * @paramstatus(OUT)The Success/Error Status.
 *
 * @returnvoid
 *
 */

void reverieGetPredictedWords(unsigned char* keycodeSeq, int keycodeLen, unsigned short words[30][30],
        int * numberOfWords, int * status,int wordIndex);

/**
 * Sets the mode for the R9 library.
 *
 * @param mode(IN)Mode is 0 for abc, 1 for Abc and 2 for ABC.
 *Mode has no effect on Indic languages.
 *
 * @return void
 *
 */
void reverieSetMode(char mode);
#ifdef __cplusplus
}
#endif
