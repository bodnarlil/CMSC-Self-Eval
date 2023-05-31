#ifndef ABSTRACTGENOME_H_
#define ABSTRACTGENOME_H_

#include <vector>

template<class T>
class AbstractGenome {
protected:
    std::vector<T> genome;

public:
    AbstractGenome() {
    }

    AbstractGenome(int n) {
        genome.resize(n);
    }

    ~AbstractGenome() {};

    void resize(int n) {
        genome.resize(n);
    }

    void fill(T x) {
        std::fill(genome.begin(), genome.end(), x);
    }

    std::vector<T> get() {
        return genome;
    }

};

#endif /* ABSTRACTGENOME_H_ */