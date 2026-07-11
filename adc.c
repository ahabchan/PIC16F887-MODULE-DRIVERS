#include "adc.h"

#define _XTAL_FREQ 4000000

/**
 * @brief Initialise le module ADC.
 *
 * Configure l'ADC avec une référence de tension comprise entre VDD et VSS,
 * un résultat justifié à droite et une horloge ADC adaptée à une fréquence
 * système de 4 MHz.
 *
 * @details
 * La conversion analogique-numérique est activée.
 * La fréquence d'horloge ADC est configurée à Fosc/32.
 *
 * @return Aucun retour.
 */
void adc_init(void) {

    // ADC ON
    ADCON0bits.ADON = 1;

    // Right justified result
    ADCON1bits.ADFM = 1;

    // Vref = VDD / VSS
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;

    // ADC clock Fosc/32 (safe for 4 MHz)
    ADCON0bits.ADCS = 0b10;
}

/**
 * @brief Active un canal analogique ADC.
 *
 * Configure la broche associée au canal en entrée et active sa fonction
 * analogique.
 *
 * @param channel Numéro du canal ADC à activer.
 *                Valeurs possibles : 0 à 13.
 *
 * @details
 * Chaque canal correspond à une entrée analogique physique différente :
 * - AN0 à AN7 utilisent le registre ANSEL.
 * - AN8 à AN13 utilisent le registre ANSELH.
 *
 * @return Aucun retour.
 */
void adc_enable_channel(uint8_t channel) {
    switch (channel) {
        case 0:
            TRISAbits.TRISA0 = 1;
            ANSELbits.ANS0 = 1;
            break;

        case 1:
            TRISAbits.TRISA1 = 1;
            ANSELbits.ANS1 = 1;
            break;

        case 2:
            TRISAbits.TRISA2 = 1;
            ANSELbits.ANS2 = 1;
            break;

        case 3:
            TRISAbits.TRISA3 = 1;
            ANSELbits.ANS3 = 1;
            break;

        case 4:
            TRISAbits.TRISA5 = 1;
            ANSELbits.ANS4 = 1;
            break;

        case 5:
            TRISEbits.TRISE0 = 1;
            ANSELbits.ANS5 = 1;
            break;

        case 6:
            TRISEbits.TRISE1 = 1;
            ANSELbits.ANS6 = 1;
            break;

        case 7:
            TRISEbits.TRISE2 = 1;
            ANSELbits.ANS7 = 1;
            break;

        case 8:
            TRISBbits.TRISB2 = 1;
            ANSELHbits.ANS8 = 1;
            break;

        case 9:
            TRISBbits.TRISB3 = 1;
            ANSELHbits.ANS9 = 1;
            break;

        case 10:
            TRISBbits.TRISB1 = 1;
            ANSELHbits.ANS10 = 1;
            break;

        case 11:
            TRISBbits.TRISB4 = 1;
            ANSELHbits.ANS11 = 1;
            break;

        case 12:
            TRISBbits.TRISB0 = 1;
            ANSELHbits.ANS12 = 1;
            break;

        case 13:
            TRISBbits.TRISB5 = 1;
            ANSELHbits.ANS13 = 1;
            break;
    }
}

/**
 * @brief Lit une valeur analogique sur un canal ADC.
 *
 * Sélectionne le canal ADC indiqué, réalise une conversion analogique-numérique
 * puis retourne le résultat de conversion.
 *
 * @param channel Numéro du canal ADC à convertir.
 *                Valeurs possibles : 0 à 13.
 *
 * @return Valeur numérique issue de la conversion ADC sur 10 bits
 *         (valeur comprise entre 0 et 1023).
 *
 * @details
 * Le temps d'acquisition est d'environ 20 µs avant le lancement de la conversion.
 * La durée totale de conversion est approximativement de 25 µs.
 */
uint16_t adc_read(uint8_t channel) {
    // Select channel (same as MOVWF ADCON0 in assembly)
    ADCON0bits.CHS = channel;

    // Acquisition time (like SampleTime in assembly)
    __delay_us(20);

    // Start conversion
    GO_nDONE = 1;

    // Wait until done
    while (GO_nDONE);

    // Return result (ADRESH + ADRESL)
    return ((uint16_t) ADRESH << 8) | ADRESL;
}