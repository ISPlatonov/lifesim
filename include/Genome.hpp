#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>


/**
 * @brief Class representing a gene.
 * 
 * A gene is a part of a genome. It contains a value, which is a float number in the range [0, 1].
 */
class Gene
{
public:
    Gene(size_t input, size_t output, float value, float bias) : input(input), output(output), value(value), bias(bias) {}
    ~Gene() = default;

    inline void mutate() {
        value += static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * .1f - .05f;
        bias += static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * .1f - .05f;
    }
    
    inline void setOutput(size_t output) { this->output = output; }
    inline void setInput(size_t input) { this->input = input; }

    inline size_t getInput() const { return input; }
    inline size_t getOutput() const { return output; }
    inline float getValue() const { return value; }
    inline float getBias() const { return bias; }

    bool operator==(const Gene& other) const {
        return input == other.getInput() && output == other.getOutput();
    }

private:
    size_t input;
    size_t output;
    float value;
    float bias;
};


// template <>
// struct std::hash<Gene>
// {
//     inline size_t operator()(const Gene& t) const {
//         return std::hash<size_t>()(t.getInput()) ^ std::hash<size_t>()(t.getOutput()) ^ std::hash<float>()(t.getValue());
//     }
// };


/**
 * @brief Class representing a genome.
 * 
 * A genome is a set of genes. It is used to create a neural network.
 */
class Genome
{
public:
    inline Genome(size_t input_nodes, size_t output_nodes) {
        this->input_nodes = input_nodes;
        this->output_nodes = output_nodes;
        for (size_t i = 0; i < input_nodes; ++i) {
            float bias = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * .1f;
            for (size_t j = 0; j < output_nodes; ++j) {
                float value = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                genes.push_back(Gene(i, j, value, bias));
            }
        }
    }
    // crossover
    inline Genome(const Genome& first, const Genome& second) {
        // the longer genome is the main one
        const auto& main_genome = first.getGenes().size() > second.getGenes().size() ? first : second;
        const auto& secondary_genome = first.getGenes().size() > second.getGenes().size() ? second : first;
        genes = main_genome.getGenes();
        input_nodes = main_genome.getInputNodes();
        output_nodes = main_genome.getOutputNodes();
        for (size_t i = 0; i < secondary_genome.getGenes().size(); ++i) {
            if (rand() % 2 == 0) {
                genes[i] = secondary_genome.getGenes()[i];
            }
        }
    }


    ~Genome() = default;

    inline void mutate() {
        if (rand() % 10 == 0) {
            create_new_gene();
        }
        size_t gene_index = rand() % genes.size();
        genes[gene_index].mutate();
    }

    inline void create_new_gene() {
        float bias = 0;
        float value = 1;
        size_t input = rand() % genes.size();
        size_t output = rand() % genes.size();
        auto new_gene = Gene(input, output, value, bias);
        if (find(genes.begin(), genes.end(), new_gene) != genes.end() || input == output) {
            return;
        }
        //genes.push_back(Gene(input, output, value, bias));
        auto it = find_if(genes.begin(), genes.end(), [input, output](const Gene& gene) { return gene.getOutput() == input; });
        if (it == genes.end()) {
            genes.push_back(new_gene);
        } else {
            it->setOutput(input);
        }
        it = find_if(genes.begin(), genes.end(), [input, output](const Gene& gene) { return gene.getInput() == output; });
        if (it != genes.end()) {
            it->setInput(output);
        }
        sort(genes.begin(), genes.end(), [](const Gene& a, const Gene& b) { return a.getInput() < b.getInput(); });
        // std::cout << "Genome: ";
        // for (auto& g : genes) {
        //     std::cout << "(" << g.getInput() << ", " << g.getOutput() << ") ";
        // }
        // std::cout << std::endl;
    }

    inline std::vector<float> getOutput(const std::vector<float>& input) const {
        // std::cout << "input: ";
        // for (auto& i : input) {
        //     std::cout << i << ' ';
        // }
        // std::cout << std::endl;
        std::vector<float> output(output_nodes, 0.f);
        for (size_t i = 0; i < input_nodes; ++i) {
            for (size_t j = 0; j < output_nodes; ++j) {
                //std::cout << output[j] << std::endl;
                output[j] += input[i] * genes[i * output_nodes + j].getValue() + genes[i * output_nodes + j].getBias();
            }
        }
        // std::cout << "output: ";
        // for (auto& o : output) {
        //     std::cout << o << ' ';
        // }
        // std::cout << std::endl;
        return output;
    }

    inline size_t getInputNodes() const { return input_nodes; }
    inline size_t getOutputNodes() const { return output_nodes; }
    inline const std::vector<Gene>& getGenes() const { return genes; }

    bool operator==(const Genome& other) const;

private:
    size_t input_nodes;
    size_t output_nodes;
    std::vector<Gene> genes;
};
