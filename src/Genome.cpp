#include "Genome.hpp"


Genome::Genome(size_t input_nodes, size_t output_nodes) {
    this->input_nodes = std::vector<Node<NodeType::Input>>(input_nodes);
    this->output_nodes = std::vector<Node<NodeType::Output>>(output_nodes);
    for (size_t i = 0; i < input_nodes; ++i) {
        float bias = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * .1f;
        for (size_t j = 0; j < output_nodes; ++j) {
            float value = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            genes.push_back(Gene(std::make_pair(NodeType::Input, i), std::make_pair(NodeType::Input, j), value, bias));
        }
    }
}


Genome::Genome(const Genome& first, const Genome& second) {
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


void Genome::mutate() {
    auto rand_num = rand();
    if (rand_num % 100 == 0) {
        create_new_node();
    } else if (rand_num % 10 == 0) {
        create_new_gene();
    } else {
        size_t gene_index = rand() % genes.size();
        genes[gene_index].mutate();
    }
}


void Genome::create_new_gene() {
    // float bias = 0;
    // float value = 1;
    // size_t input = rand() % (genes.size() + input_nodes.size());
    // auto input_node = std::make_pair(input < input_nodes.size() ? NodeType::Input : NodeType::Hidden, input < input_nodes.size() ? input : input - input_nodes.size());
    // size_t output = rand() % (genes.size() + output_nodes.size());
    // auto output_node = std::make_pair(output < hidden_nodes.size() ? NodeType::Hidden : NodeType::Output, output < hidden_nodes.size() ? output : output - hidden_nodes.size());
    // auto new_gene = Gene(input_node, output_node, value, bias);
    // if (find(genes.begin(), genes.end(), new_gene) != genes.end() || input == output) {
    //     return;
    // }
    // genes.push_back(new_gene);
    // sort(genes.begin(), genes.end(), [](const Gene& a, const Gene& b) { return a.getInput() < b.getInput(); });
}


void Genome::create_new_node() {
    Node<NodeType::Hidden> new_node;
    hidden_nodes.push_back(new_node);
    for (size_t i = 0; i < input_nodes.size(); ++i) {
        genes.push_back(Gene(std::make_pair(NodeType::Input, i), std::make_pair(NodeType::Hidden, hidden_nodes.size() - 1), 0, 0));
    }
    for (size_t i = 0; i < output_nodes.size(); ++i) {
        genes.push_back(Gene(std::make_pair(NodeType::Hidden, hidden_nodes.size() - 1), std::make_pair(NodeType::Output, i), 0, 0));
    }
}


std::vector<float> Genome::getOutput(const std::vector<float>& input) {
    for (auto& node : input_nodes) {
        node.setValue(input[node.getValue()]);
    }
    for (const auto& gene : genes) {
        const auto& input_node_pair = gene.getInput();
        const size_t input_value = input_node_pair.first == NodeType::Input ? input_nodes[input_node_pair.second].getValue() : hidden_nodes[input_node_pair.second].getValue();
        auto output_node_pair = gene.getOutput();
        auto value = gene.getValue();
        auto bias = gene.getBias();
        float result = value * input_value + bias;
        output_node_pair.first == NodeType::Hidden ? hidden_nodes[output_node_pair.second].setValue(result) : output_nodes[output_node_pair.second].setValue(result);
    }
    std::vector<float> output;
    for (const auto& node : output_nodes) {
        output.push_back(node.getValue());
    }

    return output;
}