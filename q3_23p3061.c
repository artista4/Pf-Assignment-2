#include <stdio.h>

int scoreSeries(int hand[5]);
int scoreStraight(int hand[5]);
int scoreFlush(int hand[5]);
int scoreKinds(int hand[5]);


int scoreHand(int hand[5]) 
{
    return scoreSeries(hand) + scoreKinds(hand);
}


int scoreStraight(int hand[5]) 
{
    for (int i = 1; i < 5; i++) 
    {
        if ((hand[i] % 100 + 1) != (hand[i - 1] % 100))
        return 0;
    }
    return 4000;
}


int scoreFlush(int hand[5]) 
{
    for (int i = 1; i < 5; i++) 
    {
        if ((hand[i] / 100) != (hand[i - 1] / 100))
        return 0;
    }
    return 5000;
}

int scoreSeries(int hand[5]) 
{
    int score = scoreFlush(hand) + scoreStraight(hand);

    
    if (hand[0] % 100 == 12 && score == 9000)
        return 10000;

      
    if (score > 0)
        return score + hand[0] % 100;
    return 0;
}


int scoreKinds(int hand[5]) 
{
    int counts[13] = {0}; 
    int highCards[2] = {0}; 
    int max = 1, twoSets = 0; 
    
    
   for (int i = 0; i < 5; i++) 
    {
        counts[hand[i] % 100]++;

        if (max > 1 && counts[hand[i] % 100] == 2) 
        {
            twoSets = 1;
            highCards[1] = hand[i] % 100;
        }

        // Update max occurrences
        if (max < counts[hand[i] % 100]) 
        {
            max = counts[hand[i] % 100];
            highCards[0] = hand[i] % 100;
        }
    }
   
    if (max == 1)
        return 0;
    
   
    int score = (max * 2 + twoSets) * 1000;
    if (score < 7000){
        score -= 3000;
    }
   
    if (max == 2 && twoSets == 1) 
    {
        if (highCards[1] > highCards[0]) 
        {
            int temp = highCards[0];
            highCards[0] = highCards[1];
            highCards[1] = temp;
        }
        score += 13 * highCards[0] + highCards[1];
    } 
    else 
    {
        if (counts[highCards[1]] > counts[highCards[0]]) 
        {
            int temp = highCards[0];
            highCards[0] = highCards[1];
            highCards[1] = temp;
        }
        score += highCards[0];
    }
    return score;
}

int main() 
{
    // Arrays to store hands of players
    int player1[5], player2[5];
    int i,j;

    // Input player's 1 hand
    for (i = 0; i < 5; i++)
    {
        printf("Enter the number for Player 1\nfor J input 11, Q input 12, K input 13, A input 14\n");
        scanf("%d", &player1[i]);
    }

    // Input player's 2 hand
    for (j = 0; j < 5; j++)
    {
        printf("Enter the number for Player 2\nfor J input 11, Q input 12, K input 13, A input 14\n");
        scanf("%d", &player1[j]);
    }

    // Evaluate hands and determine winner
    while (i+j==10) 
    {
        
        // Calculate scores for each player's hand
        int result1 = scoreHand(player1);
        int result2 = scoreHand(player2);

        // Compare scores and determine winner
        if (result1 > result2)
            printf("Player 1 wins\n");
        else if (result1 < result2)
            printf("Player 2 wins\n");
        else
            printf("It's a tie.\n");
        break;
    }
    return 0;
}
       