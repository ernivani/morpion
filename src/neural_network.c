#include "neural_network.h"
#include <stdlib.h>
#include <math.h>

double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

double dsigmoid(double y) {
    return y * (1 - y);
}

void init_network(NeuralNetwork *nn) {
    // Initialiser les poids et les biais avec des valeurs aléatoires
    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            nn->weights_input_hidden[i][j] = ((double)rand() / RAND_MAX) * 2 - 1; // Entre -1 et 1
        }
    }
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) {
            nn->weights_hidden_output[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;
        }
        nn->bias_hidden[i] = ((double)rand() / RAND_MAX) * 2 - 1;
    }
    for (int i = 0; i < OUTPUT_NODES; i++) {
        nn->bias_output[i] = ((double)rand() / RAND_MAX) * 2 - 1;
    }
}

void feedforward(NeuralNetwork *nn, double input[INPUT_NODES], double output[OUTPUT_NODES]) {
    double hidden[HIDDEN_NODES];

    // Calcul de la couche cachée
    for (int i = 0; i < HIDDEN_NODES; i++) {
        double sum = nn->bias_hidden[i];
        for (int j = 0; j < INPUT_NODES; j++) {
            sum += input[j] * nn->weights_input_hidden[j][i];
        }
        hidden[i] = sigmoid(sum);
    }

    // Calcul de la couche de sortie
    for (int i = 0; i < OUTPUT_NODES; i++) {
        double sum = nn->bias_output[i];
        for (int j = 0; j < HIDDEN_NODES; j++) {
            sum += hidden[j] * nn->weights_hidden_output[j][i];
        }
        output[i] = sum; // Fonction linéaire
    }
}

void train(NeuralNetwork *nn, double input[INPUT_NODES], double target[OUTPUT_NODES], double learning_rate) {
    double hidden[HIDDEN_NODES];
    double output[OUTPUT_NODES];

    // Forward pass
    feedforward(nn, input, output);

    // Calcul des erreurs de sortie
    double output_errors[OUTPUT_NODES];
    for (int i = 0; i < OUTPUT_NODES; i++) {
        output_errors[i] = target[i] - output[i];
    }

    // Calcul des erreurs de la couche cachée
    double hidden_errors[HIDDEN_NODES] = {0};
    for (int i = 0; i < HIDDEN_NODES; i++) {
        double error = 0;
        for (int j = 0; j < OUTPUT_NODES; j++) {
            error += output_errors[j] * nn->weights_hidden_output[i][j];
        }
        hidden_errors[i] = error * dsigmoid(hidden[i]);
    }

    // Mise à jour des poids entre la couche cachée et la sortie
    for (int i = 0; i < HIDDEN_NODES; i++) {
        for (int j = 0; j < OUTPUT_NODES; j++) {
            nn->weights_hidden_output[i][j] += learning_rate * output_errors[j] * hidden[i];
        }
    }

    // Mise à jour des poids entre l'entrée et la couche cachée
    for (int i = 0; i < INPUT_NODES; i++) {
        for (int j = 0; j < HIDDEN_NODES; j++) {
            nn->weights_input_hidden[i][j] += learning_rate * hidden_errors[j] * input[i];
        }
    }

    // Mise à jour des biais
    for (int i = 0; i < OUTPUT_NODES; i++) {
        nn->bias_output[i] += learning_rate * output_errors[i];
    }
    for (int i = 0; i < HIDDEN_NODES; i++) {
        nn->bias_hidden[i] += learning_rate * hidden_errors[i];
    }
}
