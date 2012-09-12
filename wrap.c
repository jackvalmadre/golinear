#include <stdlib.h>
#include <string.h>

#include <linear.h>

#include "wrap.h"

feature_node_t *nodes_new(size_t n)
{
  feature_node_t *nodes = malloc((n + 1) * sizeof(feature_node_t));

  // Terminator
  nodes[n].index = -1;
  nodes[n].value = 0.0;

  return nodes;
}

void nodes_free(feature_node_t *nodes)
{
  free(nodes);
}

void nodes_put(feature_node_t *nodes, size_t nodes_idx, int idx,
  double value)
{
  nodes[nodes_idx].index = idx;
  nodes[nodes_idx].value = value;
}

problem_t *problem_new()
{
  problem_t *problem = malloc(sizeof(problem_t));

  problem->l = 0;
  problem->n = 0;
  problem->bias = -1;
  problem->y = malloc(0);
  problem->x = malloc(0);

  return problem;
}

void problem_free(problem_t *problem)
{
  free(problem->x);
  free(problem->y);
  free(problem);
}

void problem_add_train_inst(problem_t *problem, feature_node_t *nodes,
  double label)
{
  ++problem->l;

  // The number of features equals the highest feature index.
  feature_node_t *node;
  for (node = nodes; node->index != -1; ++node)
  	if (node->index > problem->n)
  		problem->n = node->index;

  problem->y = realloc(problem->y, problem->l * sizeof(double));
  problem->y[problem->l - 1] = label;
  problem->x = realloc(problem->x, problem->l * sizeof(feature_node_t *));
  problem->x[problem->l - 1] = nodes;
}

parameter_t *parameter_new()
{
  parameter_t *param = malloc(sizeof(parameter_t));
  memset(param, 0, sizeof(parameter_t));
  return param;
}

char const *check_parameter_wrap(problem_t *prob, parameter_t *param)
{
  return check_parameter(prob, param);
}

void destroy_param_wrap(parameter_t* param)
{
  return destroy_param(param);
}

void free_and_destroy_model_wrap(model_t *model)
{
  free_and_destroy_model(&model);
}

model_t *train_wrap(problem_t *prob, parameter_t *param)
{
  return train(prob, param);
}

double predict_wrap(model_t const *model, feature_node_t *nodes)
{
  return predict(model, nodes);
}