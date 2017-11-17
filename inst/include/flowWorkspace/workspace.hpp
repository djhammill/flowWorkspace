/*
 * workspace.hpp
 *
 *  Created on: Mar 22, 2012
 *      Author: wjiang2
 */

#ifndef WORKSPACE_HPP_
#define WORKSPACE_HPP_
#include <vector>
#include <string>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include "wsNode.hpp"
#include "cytolib/transformation.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>


using namespace std;

/*TODO: so far I have seen the major difference between win and mac workspace is the xpath(like xpath of sample node)
 * if this is the case eventually we can try to use one template class (eliminate two derived classes )
 * with T structure that stores different versions of xpaths for win/mac,for example:
 *
 * struct winWorkspace{
 * xpath_sample=xxx
 * ....
 * }
 *
 * struct macWorkspace{
 * xpath_sample=xxx
 * ....
 * }
 *
 * this may potentially reduce the amount of code
 *
 */
struct xpath{
	string group;
	string sampleRef;
	string sample;
	string sampleNode;
	string popNode;
	string gateDim;
	string gateParam;

	string attrName;
	string compMatName;
	string compMatChName;
	string compMatVal;
	unsigned short sampNloc;//get FCS filename(or sampleName) from either $FIL keyword or name attribute of sampleNode
};



class workspace{
public:
	 xpath nodePath;
//protected:

	 xmlDoc * doc;

public:
	 workspace(){doc=NULL;};
	 virtual ~workspace()
	 {
			if(doc!=NULL)
			{
				xmlFreeDoc(doc);
				doc = NULL;

				/*
				 *Free the global variables that may
				 *have been allocated by the parser.
				 */
				xmlCleanupParser();
				if(g_loglevel>=GATING_SET_LEVEL)
					COUT<<"xml freed!"<<endl;
			}
	 }
	 virtual string xPathSample(string sampleID)=0;
	 virtual PARAM_VEC getTransFlag(wsSampleNode sampleNode)=0;
	 virtual trans_local getTransformation(wsRootNode,const compensation &,PARAM_VEC &,trans_global_vec *, biexpTrans * _globalBiExpTrans, linTrans * _globalLinTrans, bool prefixed)=0;
	 virtual compensation getCompensation(wsSampleNode)=0;
	 virtual trans_global_vec getGlobalTrans()=0;
	 virtual vector <string> getSampleID(unsigned short)=0;
	 virtual string getSampleName(wsSampleNode &)=0;
	 virtual wsRootNode getRoot(wsSampleNode sampleNode)=0;
	 virtual wsPopNodeSet getSubPop(wsNode *)=0;
	 virtual gate * getGate(wsPopNode &)=0;//gate is dynamically allocated within this function,it is currently freed within gate pointer owner object nodeProperties
	 virtual void to_popNode(wsRootNode &, nodeProperties &)=0;
	 virtual void to_popNode(wsPopNode &,nodeProperties &,bool isGating)=0;
	 void toArray(string sCalTable, vector<double> &x, vector<double> &y)
	 {
		 vector<string> stringVec;
		 	boost::split(stringVec,sCalTable,boost::is_any_of(","));
		 	int nLen = stringVec.size()/2;
		 	x.resize(nLen);
		 	y.resize(nLen);
		 	for(unsigned i=0;i<nLen;i++)
		 	{
		 		y[i]=atof(stringVec.at(2*i).c_str());
		 		x[i]=atof(stringVec.at(2*i + 1).c_str());
		 //		COUT<<res[i]<<",";
		 	}
	 }
	 virtual void parseVersionList(){};


};

#endif /* WORKSPACE_HPP_ */
