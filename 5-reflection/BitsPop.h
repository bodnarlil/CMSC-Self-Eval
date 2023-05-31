#ifndef BITSPOP_H_
#define BITSPOP_H_

#include "BitsOrganism.h"

class BitsPop {

    std::vector<BitsOrganism*> pop;
    int popsize;

    // added to hold the new population
    std::vector<BitsOrganism*> newpop;

public:

    BitsPop(int n, int genomesize) {
        std::cout << "hello" << std::endl;
        popsize = n;
        for (int i = 0; i < n; i++) {
            BitsOrganism* org = new BitsOrganism(genomesize);
            pop.push_back(org);
        }
    }

    void update(const std::vector<BitsOrganism*>& newpop) {
        pop = newpop;
    }

    std::vector<BitsOrganism*> getPop() {
        return pop;
    }

    BitsOrganism* getMax() {
        int currentScore = 0; int maxScore = 0; BitsOrganism* maxOrganism = pop[0];
        for (int i = 0; i < popsize; i++) {
            currentScore = (*pop[i]).getScore();
            if (currentScore > maxScore) {
                maxScore = currentScore;
                maxOrganism = pop[i];
            }
        }
        return maxOrganism;
    }

    double getMean() {
        int sum = 0; int score = 0;
        for (int i = 0; i < popsize; i++) {
            score = (*pop[i]).getScore();
            std::cout << score; // why zero?
            sum += score;
        }
        double mean = sum / popsize;
        return mean;
    }

    std::vector<BitsOrganism*> tournament_select(int tournsize) {
        if (tournsize > pop.size()) {
            // set tournsize to pop's size
            tournsize = pop.size();
        }
            std::vector<BitsOrganism*> tournPop;      // holds elements for tournament
            for (int q = 0; q < tournsize; q++) {     // run to get tournamant
                int index = rand() % popsize-1;       // random int in the range 0 to popsize-1
                tournPop.push_back(pop[index]);       // add that element at index to tournPop
                pop.erase(pop.begin() + index);       // erase that element from pop
                popsize -= 1;                         // make popsize smaller by one 
            }

            // now, tournamant has been initialized with BitsOrganisms
            // we can move on to the actual tournament itself
            int maxScore = -1; int currentScore;           // hold current and max score
            BitsOrganism* bestOrg;                    // holds best organism
            for (int w = 0; w < tournsize; w++) {     // run to get max and add to newpop
                currentScore=tournPop[w]->getScore(); // set the current score
                if (currentScore > maxScore) {        // check to see if it's better than the best
                    maxScore = currentScore;          // if it is, change score
                    bestOrg = tournPop[w];            // and update best organism
                }
            }
            newpop.push_back(bestOrg);
        return newpop;
    }

    std::vector<BitsOrganism*> roulette_select() {
        // right now, this is totally random. I need to figure out how to include the scores in this
        int popSize = pop.size();                     // initialize popSize
        int randIndex = rand() % popSize - 1;         // random int in the range 0 to popsize-1
        BitsOrganism* randomBitsOrg = pop[randIndex]; // assign a random Bits organism from pop
        newpop.push_back(randomBitsOrg);
        return newpop;
    }
};

#endif /*BITSPOP_H_*/