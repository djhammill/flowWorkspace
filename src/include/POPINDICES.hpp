/*
 * POPINDICES.hpp
 *
 *  Created on: Oct 8, 2012
 *      Author: wjiang2
 */


#ifndef POPINDICES_HPP_
#define POPINDICES_HPP_

#include <map>
#include <string>
#include <vector>
#include "gate.hpp"
#include <boost/scoped_ptr.hpp>

class POPINDICES{

	friend class boost::serialization::access;
protected:
	unsigned nEvents;
private:
	template<class Archive>
						void serialize(Archive &ar, const unsigned int version)
						{

							ar & BOOST_SERIALIZATION_NVP(nEvents);

						}


public:
	POPINDICES():nEvents(0){};
	POPINDICES(unsigned _nEvents):nEvents(_nEvents){};
	virtual ~POPINDICES(){};
	virtual vector<bool> getIndices()=0;
	virtual unsigned getCount()=0;
	unsigned getTotal(){return nEvents;}
	virtual POPINDICES * clone()=0;
	virtual void convertToPb(pb::POPINDICES & ind_pb) = 0;

};

/*
 * bool vector
 */
class BOOLINDICES:public POPINDICES{
	friend class boost::serialization::access;
private:
	vector <bool> x;
	template<class Archive>
						void save(Archive & ar, const unsigned int version) const
							{

								ar & boost::serialization::make_nvp("POPINDICES",boost::serialization::base_object<POPINDICES>(*this));

								/*
								 * pack bits into bytes
								 */
								unsigned nBits=x.size();
								unsigned nBytes=ceil(float(nBits)/8);
								vector<unsigned char> x_bytes(nBytes,0);
								for(unsigned i =0 ; i < nBits; i++) {
									unsigned byteIndex = i / 8;
									unsigned bitIndex = i % 8;
									if(x[i]) {
									    // set bit
										unsigned char mask  = 1 << bitIndex;
										x_bytes[byteIndex] = x_bytes[byteIndex] | mask;
									}
								}
								ar & BOOST_SERIALIZATION_NVP(x_bytes);
//
							}
	template<class Archive>
						void load(Archive & ar, const unsigned int version) {
								ar & boost::serialization::make_nvp("POPINDICES",boost::serialization::base_object<POPINDICES>(*this));
								if(version>0){
//									COUT<<"unpacking bits"<<endl;
									unsigned nBits=nEvents;
									unsigned nBytes=ceil(float(nBits)/8);
									vector<unsigned char> x_bytes(nBytes,0);
									x.resize(nBits,false);
									ar & BOOST_SERIALIZATION_NVP(x_bytes);
									/*
									 * unpack bytes into bits
									 */
									for(unsigned i =0 ; i < nBits; i++) {
										unsigned byteIndex = i / 8;
										unsigned bitIndex = i % 8;

										x[i] = x_bytes[byteIndex] & (1 << bitIndex);
									}

								}
								else
								{
//									COUT<<"old version."<<endl;
									ar & BOOST_SERIALIZATION_NVP(x);
								}

							}

	  BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
	BOOLINDICES():POPINDICES(){};
	BOOLINDICES(vector <bool> _ind);
	vector<bool> getIndices();
	unsigned getCount();

	POPINDICES * clone();
	void convertToPb(pb::POPINDICES & ind_pb);
	BOOLINDICES(pb::POPINDICES & ind_pb);

};
BOOST_CLASS_VERSION(BOOLINDICES,1)
/*
 * int vector
 */
class INTINDICES:public POPINDICES{
	friend class boost::serialization::access;
private:
	vector <unsigned> x;
	template<class Archive>
							void serialize(Archive &ar, const unsigned int version)
							{
								ar & boost::serialization::make_nvp("POPINDICES",boost::serialization::base_object<POPINDICES>(*this));
								ar & BOOST_SERIALIZATION_NVP(x);

							}


public:
	INTINDICES():POPINDICES(){};
	INTINDICES(vector <bool> _ind);
	INTINDICES(pb::POPINDICES & ind_pb);
	vector<bool> getIndices();
	unsigned getCount();
	POPINDICES * clone();
	void convertToPb(pb::POPINDICES & ind_pb);
};

/*
 * root node
 */
class ROOTINDICES:public POPINDICES{
	friend class boost::serialization::access;
private:

	template<class Archive>
							void serialize(Archive &ar, const unsigned int version)
							{
								ar & boost::serialization::make_nvp("POPINDICES",boost::serialization::base_object<POPINDICES>(*this));
							}


public:
	ROOTINDICES():POPINDICES(){};
	ROOTINDICES(unsigned _nEvents):POPINDICES(_nEvents){};
	ROOTINDICES(pb::POPINDICES & ind_pb);
	vector<bool> getIndices();
	unsigned getCount();
	POPINDICES * clone();
	void convertToPb(pb::POPINDICES & ind_pb);
};


#endif /* POPINDICES_HPP_ */
