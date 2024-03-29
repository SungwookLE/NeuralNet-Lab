// g++ build Command(terminal): g++ neural_net.cpp readCSV.cpp -o neuralnet.exe

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <random>
#include "readCSV.h"

double activate_sigmoid(double in)
{
	double res;
	res = (double)1.0 / (1.0 + std::exp(-in));

	return res;
}

double activate_relu(double in)
{
	double res;

	if (in >= 0)
		res = in;
	else
		res = 0.0;

	return res;
}

double activate_step(double in)
{
	double res;

	if (in >= 0)
		res = 1.0;
	else
		res = 0.0;

	return res;
}

double forawrd_inferencing(const std::vector<double> X, const std::vector<double> W, const double B, const std::string opt)
{
	double res;
	double ans;

	res = X.at(0) * W[0] + X.at(1) * W[1] + B;

	if (opt == "relu")
	{
		ans = activate_relu(res);
	}
	else if (opt == "step")
	{
		ans = activate_step(res);
	}
	else // (opt == "sigmoid")
	{
		ans = activate_sigmoid(res);
	}

	return ans;
}

void backward_propagation(std::vector<double> &link_chain, int node_relation, const double output, const std::vector<double> input, std::vector<double> &W, double &B, double learning_rate, const std::string opt)
{

	double gradient_W0, gradient_W1, gradient_B;
	double link_value = link_chain[node_relation];
	link_chain.clear();

	if (opt == "sigmoid")
	{
		gradient_W0 = link_value * (1 - output) * output * input[0];
		gradient_W1 = link_value * (1 - output) * output * input[1];
		gradient_B = link_value * (1 - output) * output * 1;

		W[0] = W[0] - learning_rate * gradient_W0;
		W[1] = W[1] - learning_rate * gradient_W1;
		B = B - learning_rate * gradient_B;

		link_chain.push_back(link_value * (1 - output) * output * W[0]);
		link_chain.push_back(link_value * (1 - output) * output * W[1]);
	}
	else if (opt == "relu")
	{
		double net = input[0] * W[0] + input[1] * W[1] + B;
		if (net >= 0)
		{
			gradient_W0 = link_value * input[0];
			gradient_W1 = link_value * input[1];
			gradient_B = link_value * 1;

			W[0] = W[0] - learning_rate * gradient_W0;
			W[1] = W[1] - learning_rate * gradient_W1;
			B = B - learning_rate * gradient_B;

			link_chain.push_back(link_value * W[0]);
			link_chain.push_back(link_value * W[1]);
		}
		else
		{
			W[0] = W[0];
			W[1] = W[1];
			B = B;

			link_chain.push_back(0);
			link_chain.push_back(0);
		}
	}

	return;
}

int main()
{

	unordered_map<string, double> initWeight;
	unordered_map<string, double> finalWeight;

	/* 1. Data Set Read:
		DATA STRUCTURE
		{   {X1, X2, LABEL}
			{X1, X2, LABEL}
			{X1, X2, LABEL}
			...
		}
		GROUP_A HAS LABEL '1', GROUP HAS LABEL '0'
	*/
	std::vector<std::vector<double>> group_a;
	std::vector<std::vector<double>> group_b;
	read_csv("./data/dataSet.csv", group_a, group_b);
	std::vector<std::vector<double>> data_set;
	data_set.insert(data_set.end(), group_a.begin(), group_a.end());
	data_set.insert(data_set.end(), group_b.begin(), group_b.end());

	/* 2. Random Number Gen */
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> dist(0, 0.25);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TO-DO 1: Initializing the Weights and Bias

	/* 2-1. Initialization of Node weights and bias */
	std::vector<double> W_o1 = ; // weights
	double B_o1 = ;				 // bias
	std::cout << "Initial={\"W_o1[0]\":" << W_o1[0] << ", "
			  << "\"W_o1[1]\":" << W_o1[1] << ", "
			  << "\"B_o1\":" << B_o1 << "}" << std::endl;

	std::vector<double> W_h1 = ; // weights
	double B_h1 = ;				 // bias
	std::cout << "Initial={\"W_h1[0]\":" << W_h1[0] << ", "
			  << "\"W_h1[1]\":" << W_h1[1] << ", "
			  << "\"B_h1\":" << B_h1 << "}" << std::endl;

	std::vector<double> W_h2 = ; // weights
	double B_h2 = ;				 // bias
	std::cout << "Initial={\"W_h2[0]\":" << W_h2[0] << ", "
			  << "\"W_h2[1]\":" << W_h2[1] << ", "
			  << "\"B_h2\":" << B_h2 << "}" << std::endl;

	initWeight["W_o1[0]"] = W_o1[0];
	initWeight["W_o1[1]"] = W_o1[1];
	initWeight["B_o1"] = B_o1;

	initWeight["W_h1[0]"] = W_h1[0];
	initWeight["W_h1[1]"] = W_h1[1];
	initWeight["B_h1"] = B_h1;

	initWeight["W_h2[0]"] = W_h2[0];
	initWeight["W_h2[1]"] = W_h2[1];
	initWeight["B_h2"] = B_h2;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* 3. Learning with Backpropagation */
	int iteration = 10000;
	double learning_rate = 0.01;
	for (int iter = 0; iter < iteration; ++iter)
	{
		for (int i = 0; i < data_set.size(); ++i)
		{
			// batch size: 1
			std::vector<double> feed_data = {data_set[i][0], data_set[i][1]};
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			// TO-DO 2: Fill the FORWARD INFERENCING

			// 3-1. FORWARD Inferencing
			double out_h1 = ;
			double out_h2 = ;
			double out_o1 = ;

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 3-2. BACKWARD PROPAGATION
			std::vector<double> link_chain;
			link_chain.push_back(-(data_set[i][2] - out_o1));
			backward_propagation(link_chain, 0, out_o1, {out_h1, out_h2}, W_o1, B_o1, learning_rate, "sigmoid");
			backward_propagation(link_chain, 0, out_h1, {data_set[i][0], data_set[i][1]}, W_h1, B_h1, learning_rate, "sigmoid");
			backward_propagation(link_chain, 1, out_h2, {data_set[i][0], data_set[i][1]}, W_h2, B_h2, learning_rate, "sigmoid");
		}
		// MONITOR
		if (iter % 100 == 0)
		{
			/* DEBUG 1: Forward Inferencing */
			std::vector<double> out_net;
			for (int i = 0; i < data_set.size(); ++i)
			{
				std::vector<double> res = {data_set.at(i)[0], data_set.at(i)[1]};

				double out_h1 = forawrd_inferencing(res, W_h1, B_h1, "sigmoid");
				double out_h2 = forawrd_inferencing(res, W_h2, B_h2, "sigmoid");
				res = {out_h1, out_h2};
				double out_o1 = forawrd_inferencing(res, W_o1, B_o1, "sigmoid");
				out_net.push_back(out_o1);
			}

			/* DEBUG 2: Check SCORE */
			int score = 0;
			for (int i = 0; i < data_set.size(); ++i)
			{
				int label_est = std::round(out_net[i]);
				if (label_est == data_set[i][2])
					score += 1;
			}
			/*DEBUG 3: PRINT */
			std::cout << iter << "th ITERATION(" << score << "/" << out_net.size() << "): " << (double)score / out_net.size() * 100 << "%" << std::endl;
		}
	}

	std::cout << "Result={\"W_o1[0]\":" << W_o1[0] << ", "
			  << "\"W_o1[1]\":" << W_o1[1] << ", "
			  << "\"B_o1\":" << B_o1 << "}" << std::endl;
	std::cout << "Result1={\"W_h1[0]\":" << W_h1[0] << ", "
			  << "\"W_h1[1]\":" << W_h1[1] << ", "
			  << "\"B_h1\":" << B_h1 << "}" << std::endl;
	std::cout << "Result2={\"W_h2[0]\":" << W_h2[0] << ", "
			  << "\"W_h2[1]\":" << W_h2[1] << ", "
			  << "\"B_h2\":" << B_h2 << "}" << std::endl;

	finalWeight["W_o1[0]"] = W_o1[0];
	finalWeight["W_o1[1]"] = W_o1[1];
	finalWeight["B_o1"] = B_o1;

	finalWeight["W_h1[0]"] = W_h1[0];
	finalWeight["W_h1[1]"] = W_h1[1];
	finalWeight["B_h1"] = B_h1;

	finalWeight["W_h2[0]"] = W_h2[0];
	finalWeight["W_h2[1]"] = W_h2[1];
	finalWeight["B_h2"] = B_h2;

	/* 4. Forward Inferencing */
	std::vector<double> out_net;
	for (int i = 0; i < data_set.size(); ++i)
	{
		std::vector<double> feed_data = {data_set[i][0], data_set[i][1]};
		// 3-1. FORWARD PROPAGATION
		double out_h1 = forawrd_inferencing(feed_data, W_h1, B_h1, "sigmoid");
		double out_h2 = forawrd_inferencing(feed_data, W_h2, B_h2, "sigmoid");
		double out_o1 = forawrd_inferencing({out_h1, out_h2}, W_o1, B_o1, "sigmoid");
		out_net.push_back(out_o1);
	}

	/* 5. SCORE with CSV export */
	int score = 0;
	for (int i = 0; i < data_set.size(); ++i)
	{
		int label_est = std::round(out_net[i]);
		if (label_est == data_set[i][2])
			score += 1;
	}
	std::vector<double> label_a, label_b;
	label_a.insert(label_a.begin(), out_net.begin(), out_net.begin() + 100);
	label_b.insert(label_b.begin(), out_net.begin() + 100, out_net.end());
	save_csv("results/resultNeural.csv", group_a, group_b, label_a, label_b, initWeight, finalWeight, 2);
	std::cout << "VALIDATION(" << score << "/" << out_net.size() << "): " << (double)score / out_net.size() * 100 << "%" << std::endl;

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TO-DO 3: DISCUSSION THE RESULTS
// The results may not be shown always better than singleLayer. Explain the reason why

//////////////////////////////////////////////////////////////////////////////////////////////////////////
