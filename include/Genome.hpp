#pragma once

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>


enum class NodeType
{
    Input,
    Hidden,
    Output
};


template <NodeType T>
class Node
{
public:
    Node<T>(float value = 0.f) : value(value), type(T) {}
    ~Node() = default;

    inline void setValue(float value) { this->value = value; }
    inline float getValue() const { return value; }
    inline NodeType getType() const { return type; }

private:
    float value;
    NodeType type;
};


/**
 * @brief Class representing a gene.
 * 
 * A gene is a part of a genome. It contains a value, which is a float number in the range [0, 1].
 */
class Gene
{
public:
    Gene(std::pair<NodeType, size_t> input, std::pair<NodeType, size_t> output, float value, float bias) : input(input), output(output), value(value), bias(bias) {}
    ~Gene() = default;

    inline void mutate() {
        value += static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * .1f - .05f;
        bias += static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * .1f - .05f;
    }
    

    inline std::pair<NodeType, size_t> getInput() const { return input; }
    inline std::pair<NodeType, size_t> getOutput() const { return output; }
    inline float getValue() const { return value; }
    inline float getBias() const { return bias; }

    bool operator==(const Gene& other) const {
        return input == other.getInput() && output == other.getOutput();
    }

protected:
    inline void setOutput(std::pair<NodeType, size_t> output) { this->output = output; }
    inline void setInput(std::pair<NodeType, size_t> input) { this->input = input; }

private:
    std::pair<NodeType, size_t> input;
    std::pair<NodeType, size_t> output;
    float value;
    float bias;
};


/**
 * @brief Class representing a genome.
 * 
 * A genome is a set of genes. It is used to create a neural network.
 */
class Genome
{
public:
    Genome(size_t input_nodes, size_t output_nodes);
    Genome(const Genome& first, const Genome& second);
    ~Genome() = default;

    void mutate();
    std::vector<float> getOutput(const std::vector<float>& input);

    inline const std::pair<size_t, size_t> ioSize() const { return {input_nodes.size(), output_nodes.size()}; }
    inline const std::vector<Gene>& getGenes() const { return genes; }

    inline bool operator==(const Genome& other) const { return genes == other.getGenes(); }

protected:
    inline std::vector<Node<NodeType::Input>> getInputNodes() const { return input_nodes; }
    inline std::vector<Node<NodeType::Output>> getOutputNodes() const { return output_nodes; }
    inline std::vector<Node<NodeType::Hidden>> getHiddenNodes() const { return hidden_nodes; }
    
    void create_new_gene();
    void create_new_node();

private:
    std::vector<Node<NodeType::Input>> input_nodes;
    std::vector<Node<NodeType::Output>> output_nodes;
    std::vector<Node<NodeType::Hidden>> hidden_nodes;
    std::vector<Gene> genes;
};
