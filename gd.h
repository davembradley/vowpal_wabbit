/*
Copyright (c) 2009 Yahoo! Inc.  All rights reserved.  The copyrights
embodied in the content of this file are licensed under the BSD
(revised) open source license
 */

#ifndef GD_H
#define GD_H

#include "math.h"
#include "parse_example.h"
using namespace std;

void print_result(int f, float res, v_array<char> tag);

struct gd_vars
{ 
  long long int example_number;
  double weighted_examples;
  double old_weighted_examples;
  double weighted_labels;
  size_t total_features;
  float eta;
  int daemon;
  int predictions, raw_predictions;
  double sum_loss;
  double sum_loss_since_last_dump;
  float t;
  float power_t;
  float dump_interval;
  float min_prediction;
  float max_prediction;
  bool quiet;
  bool training;
  
  void (*print)(int,float,v_array<char>);

  gd_vars()
  {};

  void init()
  {
    weighted_examples = 0.;
    example_number = 0;
    weighted_labels = 0.;
    total_features = 0;
    daemon = -1;
    predictions = -1;
    raw_predictions = -1;
    sum_loss = 0.0;
    sum_loss_since_last_dump = 0.0;
    t = 1.;
    power_t = 0.;
    dump_interval = exp(1.);
    min_prediction = 0.;
    max_prediction = 1.;
    old_weighted_examples = 0.;
    quiet = false;
    training = true;
    eta = 0.1;
    print = print_result;
  }
};

struct go_params
{
  gd_vars* vars;
  size_t thread_num;
  regressor reg;
  string* final_regressor_name;

  void init(gd_vars* in_vars, regressor& reg_in, string* final_regressor_name_in, size_t in_tn)
  {
    vars = in_vars;
    reg = reg_in;
    final_regressor_name = final_regressor_name_in;
    thread_num = in_tn;
  }
};

struct label_data {
  double label;
  float weight;
  bool undo;
  v_array<char> tag;
};

size_t read_cached_simple_label(void* v, io_buf& cache);
void cache_simple_label(void* v, io_buf& cache);
void default_simple_label(void* v);
void parse_simple_label(void* v, substring label_space, v_array<substring>& words);
void delete_simple_label(void* v);
const label_parser simple_label = {default_simple_label, parse_simple_label, 
				   cache_simple_label, read_cached_simple_label, 
				   delete_simple_label, sizeof(label_data)};

float final_prediction(float ret, size_t num_features, float &norm);

float predict(weight* weights, const v_array<feature> &features);
float predict(regressor& r, example* ex, size_t thread_num, gd_vars& vars);
float offset_predict(regressor& r, example* ex, size_t thread_num, gd_vars& vars, size_t offset);

float inline_predict(regressor &reg, example* &ec, size_t thread_num);

float one_of_quad_predict(v_array<feature> &page_features, feature& offer_feature, weight* weights, size_t mask);

float one_pf_quad_predict(weight* weights, feature& page_feature, v_array<feature> &offer_features, size_t mask);

float single_quad_weight(weight* weights, feature& page_feature, feature* offer_feature, size_t mask);

void inline_train(regressor &reg, example* &ec, size_t thread_num, float update);

void quadratic(v_array<feature> &f, const v_array<feature> &first_part, 
               const v_array<feature> &second_part, size_t thread_mask);

void train(weight* weights, const v_array<feature> &features, float update);

void train_one_example(regressor& r, example* ex, size_t thread_num, gd_vars& vars);
void train_offset_example(regressor& r, example* ex, size_t thread_num, gd_vars& vars, size_t offset);
void compute_update(example* ec, gd_vars& vars);
void offset_train(regressor &reg, example* &ec, size_t thread_num, float update, size_t offset);
void train_one_example_single_thread(regressor& r, example* ex, gd_vars& vars);

#endif
