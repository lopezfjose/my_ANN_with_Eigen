/*
		Author:		He Zhichao
		date:			2018.09.05
		version:		v0.1
		E-mail:			mario.he@goertek.com
*/

/*
		������ʹ��Eigen���������ʵ�ֶ��ȫ�����������
	ǰ�򴫲���forward���뷴�򴫲���backpropagation����
*/

#ifndef NET_H
#define NET_H

#pragma once

#include <iostream>
#include <vector>
#include "Dense"

namespace mario
{
	class Net
	{
	public:
	//private
		std::vector<int> m_layerNeuronNum;
		std::vector<std::string> m_actvationFunctions;

		std::vector<Eigen::MatrixXd> m_neurons;
		std::vector<Eigen::MatrixXd> m_weights;
		std::vector<Eigen::MatrixXd> m_bias;

		//��i����Ԫ�ĵ�����deltaError�����ڵ�i-1��vector
		std::vector<Eigen::MatrixXd> m_deltaWeights;
		std::vector<Eigen::MatrixXd> m_deltaBias;
		std::vector<Eigen::MatrixXd> m_derivativeNeurons;
		std::vector<Eigen::MatrixXd> m_deltaError;

		Eigen::MatrixXd m_targetOutput;
		Eigen::MatrixXd m_input;

		double m_learningRate;
		double m_loss;

	protected:
		void initWeights();			//��ʼ��Ȩ��
		void initBias();					//��ʼ��ƫ��
		void initNeurons();			//��ʼ����Ԫ
		void initDeltaWeights();					//��ʼ���ݶ�
		void initDeltaBias();
		void initDerivativeNeurons();			//��ʼ����Ԫ����������ĵ������ӵڶ�������Ϊ1���㿪ʼ<ǰ�򴫲���ʱ����㼤�������
		void initDeltaError();
		Eigen::MatrixXd activationFunction(const Eigen::MatrixXd &input, const std::string &actvationFuntion);

	public:
		Net(const std::vector<int> &layerNeuronNum, const std::vector<std::string> &activationFunctions)
			: m_layerNeuronNum(layerNeuronNum), m_actvationFunctions(activationFunctions)
		{
			if (layerNeuronNum.size() != (activationFunctions.size() + 1))
			{
				std::cout << "layerNeuronNum.size != activationFunctions.size" << std::endl;
			}

			if (layerNeuronNum.size() <= 1)
			{
				std::cout << "layerNeuronNum.size() <= 1" << std::endl;
			}

			//Debug
		}

		void initANN();
		
		//�ڼ���ǰ�򴫲��У�˳���ÿ����Ԫ������ĵ��������� m_derivativeNeurons �������
		void forward();	

		void calcDeltaError();

		void calcGradient();

		void updateParams();

		void load();

		void train(double learninigRate = 0.3, double decay = 0.5, int decayNum = 100, int epoch = 1000);
	};	//class Net
}

#endif	//NET_H
