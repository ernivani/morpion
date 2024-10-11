#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#define INPUT_NODES 9
#define HIDDEN_NODES 18
#define OUTPUT_NODES 9

typedef struct {
    double weights_input_hidden[INPUT_NODES][HIDDEN_NODES];
    double weights_hidden_output[HIDDEN_NODES][OUTPUT_NODES];
    double bias_hidden[HIDDEN_NODES];
    double bias_output[OUTPUT_NODES];
} NeuralNetwork;

void init_network(NeuralNetwork *nn);
void feedforward(NeuralNetwork *nn, double input[INPUT_NODES], double output[OUTPUT_NODES]);
void train(NeuralNetwork *nn, double input[INPUT_NODES], double target[OUTPUT_NODES], double learning_rate);

#endif
