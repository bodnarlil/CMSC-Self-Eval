import random
import copy
import matplotlib.pyplot as plt

class Genome:
    # Constructor
    def __init__(self, n):
        self.n = n
        self.sites = [random.randint(0, 1) for _ in range(n)]
    
    # Single locus flip at a site 
    def flip(self, i):
        if self.sites[i] == 0:
            self.sites[i] = 1
        else:
            self.sites[i] = 0

    def __str__(self):
        return str(self.sites)

class Organism:
    # Constructor
    def __init__(self, genome_size):
        self.n = genome_size
        self.genome = Genome(self.n)
        self.fitness = self.score()
    
    # "maxone" scoring function
    def score(self):
        return sum(self.genome.sites)/(self.genome.n)

    # single flip mutation at some random locus 
    def mutate(self):
        locus = random.randrange(0, self.n)
        self.genome.flip(locus)
    
    # easy mutate
    def easy_mutate(self):
        locus = random.randrange(0, self.n)
        self.genome.sites[locus] = 1

    # Define less-than operator so we can compare organisms directly
    def __lt__(self, other):
        return self.fitness < other.fitness

    # Define repr so we can print the organism
    def __repr__(self):
        return "Org" + str(self.genome.sites)

class Population:

    # Constructor
    def __init__(self, n, genome_size):
        self.popsize = n
        self.pop = [Organism(genome_size) for _ in range(self.popsize)]
    
    # Tournament selection
    def tournament(self, tourny_size):
        winners = []                                                
        while len(winners) < self.popsize:                          
            tourny = random.choices(self.pop, k=tourny_size)       
            winners.append(copy.deepcopy(max(tourny)))
        return winners

    # Overwrite the current population with a new population 
    def update(self, newpop):
        self.pop = copy.deepcopy(newpop)

    # Find the maximal organism
    def get_best(self):
        return max(self.pop)
    
    # Find the score of the maximal organism
    def get_best_fitness(self):
        return self.get_best().score()
    
    # Find the average score across all organisms in the population
    def get_avg_fitness(self):
        total = sum([org.score() for org in self.pop])
        return total/self.popsize
    


popsize = 100
genomesize = 1000
n_generations = 1000
avgfit = []
bestfit = []

population = Population(popsize, genomesize)

# Evolution Loop!
for _ in range(n_generations):
    # Selection 
    newpop = population.tournament(7)

    # Variation
    for org in newpop:
        #org.mutate()
        org.easy_mutate()

    # Heritability 
    population.update(newpop)

    avgfit.append(population.get_avg_fitness())
    bestfit.append(population.get_best_fitness())

plt.plot(range(n_generations), avgfit)
plt.plot(range(n_generations), bestfit)
plt.show()