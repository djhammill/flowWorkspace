/*
 * flowJoWorkspace.cpp
 *
 *  Created on: Mar 15, 2012
 *      Author: wjiang2
 */
#include "include/flowJoWorkspace.hpp"
#include <string>
//#include <libxml/tree.h>
#include <libxml/parser.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>

const double PI  =3.141592653589793238462;
using namespace std;


/*constructors of flowJoWorkspace for mac and win derived classes
 *
 */

macFlowJoWorkspace::macFlowJoWorkspace(xmlDoc * doc){
	cout<<"mac version of flowJo workspace recognized."<<endl;

	nodePath.group="/Workspace/Groups/GroupNode";
	nodePath.sampleRef=".//SampleRef";
	nodePath.sample="/Workspace/SampleList/Sample";
	nodePath.sampleNode="./SampleNode";
	nodePath.popNode="./Population";
	this->doc=doc;

}
winFlowJoWorkspace::winFlowJoWorkspace(xmlDoc * doc){
	cout<<"windows version of flowJo workspace recognized."<<endl;
//	xpath_sample="/Workspace/SampleList/Sample/DataSet";
	nodePath.group="/Workspace/Groups/GroupNode";// abs path
	nodePath.sampleRef=".//SampleRef";//relative GroupNode
	nodePath.sample="/Workspace/SampleList/Sample";//abs path
	nodePath.sampleNode="./SampleNode";//relative to sample
	nodePath.popNode="./*/Population";//relative to sampleNode
	this->doc=doc;

}


/*get a vector of sampleID by the given groupID
 * keep the returned results in char * format in case the non-numeric sampleID is stored
 * make sure to free the memory of xmlChar * outside of the call
 */
vector<string> flowJoWorkspace::getSampleID(unsigned short groupID)
{

		xmlXPathContextPtr context = xmlXPathNewContext(doc);
		xmlXPathObjectPtr result = xmlXPathEval((xmlChar *)nodePath.group.c_str(), context);
		if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
			xmlXPathFreeObject(result);
			xmlXPathFreeContext(context);
//	                cout<<"No Groups"<<endl;;
	         throw(domain_error("No Groups infomation!"));
		}

		if(groupID<0||groupID>=result->nodesetval->nodeNr)
		{
			xmlXPathFreeObject(result);
			xmlXPathFreeContext(context);
			 throw(invalid_argument("invalid GroupID provided!"));
		}
		xmlNodePtr cur=result->nodesetval->nodeTab[groupID];
		context->node=cur;
		xmlXPathObjectPtr sids=xmlXPathEval((xmlChar *)nodePath.sampleRef.c_str(),context);
		vector<string> sampleID;
		xmlNodeSetPtr nodeSet=sids->nodesetval;
		int size=nodeSet->nodeNr;

		for(int i=0;i<size;i++)
		{
			xmlNodePtr curNode=nodeSet->nodeTab[i];
			xmlChar * curSampleID= xmlGetProp(curNode,(xmlChar *)"sampleID");
			//to avoid memory leaking,store a copy of returned characters in string vector so that the dynamically allocated memory
			//can be freed right away in stead of later on.
			string sSampleID=(const char *)curSampleID;
			sampleID.push_back(sSampleID.c_str());
			xmlFree(curSampleID);
		}
//			;

		xmlXPathFreeObject (result);
		xmlXPathFreeContext(context);
		xmlXPathFreeObject (sids);
		return(sampleID);
}

string macFlowJoWorkspace::xPathSample(string sampleID){
			string xpath=nodePath.sample;
			xpath.append("[@sampleID='");
			xpath.append(sampleID);
			xpath.append("']");
			return xpath;

}

string winFlowJoWorkspace::xPathSample(string sampleID){
			string xpath=nodePath.sample;
			xpath.append("/DataSet[@sampleID='");
			xpath.append(sampleID);
			xpath.append("']/..");
			return xpath;

}


//need to explicitly release the memory after this call
string flowJoWorkspace::getSampleName(wsSampleNode & node){

	xmlXPathObjectPtr res=node.xpathInNode("SampleNode");//get sampleNode
	wsNode sampleNode(res->nodesetval->nodeTab[0]);
	xmlXPathFreeObject(res);

	return sampleNode.getProperty("name");//get property name from sampleNode

}

//bool matchName(calibrationTable calTbl){
//
//	return calTbl.name.find("Acquisition-defined")==string::npos;
//}
/*
 * get transformation for one particular sample node
 */
trans_map macFlowJoWorkspace::getTransformation(wsSampleNode,string cid,trans_vec * trans){

//	if(dMode>=GATING_HIERARCHY_LEVEL)
//			cout<<"parsing transformation..."<<endl;

	trans_map res;
	if(cid.compare("-1")==0)
	{
		/*
		 * look for Acquisition-defined witin global calitbls
		 */
		for(trans_vec::iterator it=trans->begin();it!=trans->end();it++)
		{
			transformation* curTbl=*it;
			if(curTbl->name.find("Acquisition-defined")!=string::npos)
			{

				res[curTbl->channel]=curTbl;
				if(dMode>=GATING_HIERARCHY_LEVEL)
					cout<<"adding "<<curTbl->name<<":"<<curTbl->channel<<endl;
			}
		}
//		CALTBS::iterator it=find(calTbls->begin(),calTbls->end(),matchName);
//		if(it==calTbls->end())
//			throw(domain_error("can't find Acquisition-defined calibration table"));

	}
	else if(cid.compare("-2")==0)
	{

	}
	else
	{

	}
	return res;
}

trans_map winFlowJoWorkspace::getTransformation(wsSampleNode,string cid,trans_vec * trans){

//	if(dMode>=GATING_HIERARCHY_LEVEL)
//			cout<<"parsing transformation..."<<endl;

	trans_map res;


	for(trans_vec::iterator it=trans->begin();it!=trans->end();it++)
	{
		transformation* curTran=*it;
		if(curTran->name.find(cid)!=string::npos)
		{

			res[curTran->channel]=curTran;
			if(dMode>=GATING_HIERARCHY_LEVEL)
				cout<<"adding "<<curTran->name<<":"<<curTran->channel<<endl;
		}
	}


	return res;
}

/*
 * parse global transformation functions/calibration tables
 * currently we only extract current used group of trans assuming samples in workspace
 * will choose from "current" group.
 */
trans_vec winFlowJoWorkspace::getGlobalTrans(){

	trans_vec res;



	string path="/Workspace/CompensationEditor";
	xmlXPathContextPtr context = xmlXPathNewContext(doc);
	xmlXPathObjectPtr CompEdres = xmlXPathEval((xmlChar *)path.c_str(), context);
	if(xmlXPathNodeSetIsEmpty(CompEdres->nodesetval))
	{
		cout<<"no CompensationEditor found!"<<endl;
		xmlXPathFreeObject(CompEdres);
		xmlXPathFreeContext(context);
		return(res);
	}
	wsNode compEdNode(CompEdres->nodesetval->nodeTab[0]);
	/*
	 * TODO::maybe we should get all available transformation groups from here instead of only one
	 * in case samples would choose from multiple pre-defined trans groups
	 */
	string curCompName=compEdNode.getProperty("current");//get current used compensation/trans node
	if(curCompName.empty())
	{
		cout<<"no current compensation name found!"<<endl;
		xmlXPathFreeObject(CompEdres);
		xmlXPathFreeContext(context);
		return(res);
	}
	xmlXPathFreeObject(CompEdres);
	xmlXPathFreeContext(context);

	path="Compensation[@name='"+curCompName+"']";
	xmlXPathObjectPtr compNodeRes=compEdNode.xpathInNode(path);

	if(compNodeRes->nodesetval->nodeNr!=1)
	{
		cout<<"the number of compensation matched is not 1!"<<endl;
		xmlXPathFreeObject(compNodeRes);
		return(res);
	}
	wsNode compNode(compNodeRes->nodesetval->nodeTab[0]);
	xmlXPathFreeObject(compNodeRes);

	path="//*[local-name()='logicle']";//|*[local-name()='biex']");
	xmlXPathObjectPtr compRes=compNode.xpathInNode(path);
	for(int i=0;i<compRes->nodesetval->nodeNr;i++)
	{
		wsNode transNode(compRes->nodesetval->nodeTab[i]);

		string pname=transNode.getProperty("parameter");
		if(pname.empty())
			continue;//skip the tables without channel info

		string transType=(const char*)transNode.thisNode->name;
		if(transType.compare("logicle")==0)
		{

			if(dMode>=GATING_SET_LEVEL)
				cout<<"parsing logicle tranformation:"<<":"<<pname<<endl;
			biexpTrans *curTran=new biexpTrans();
			curTran->name=curCompName;
			curTran->channel=pname;
			curTran->pos=atof(transNode.getProperty("T").c_str());
			curTran->neg=atof(transNode.getProperty("w").c_str());
			curTran->widthBasis=atof(transNode.getProperty("m").c_str());
			res.push_back(curTran);
		}
		else
			throw(domain_error("unknown tranformation type!"));

	}

	xmlXPathFreeObject(compRes);

	return res;
}

trans_vec macFlowJoWorkspace::getGlobalTrans(){

	trans_vec res;



	string path="/Workspace/CalibrationTables/Table";
	xmlXPathContextPtr context = xmlXPathNewContext(doc);
	xmlXPathObjectPtr result = xmlXPathEval((xmlChar *)path.c_str(), context);
	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		cout<<"no calibration Tables found!"<<endl;
		return(res);
	}
	for(int i=0;i<result->nodesetval->nodeNr;i++)
	{
		wsNode calTblNode(result->nodesetval->nodeTab[i]);

		transformation *curTran=new transformation();
		calibrationTable *t=new calibrationTable("flowJo",2);
		string tname=calTblNode.getProperty("name");
		if(tname.empty())
			throw(domain_error("empty name for calibration table"));
		/*
		 * parse the string from tname to extract channel name
		 */
		size_t nPrefix=tname.find("<");
		size_t nsuffix=tname.find(">");
		if((nPrefix==string::npos)|(nsuffix==string::npos))
			continue;//skip the tables without channel info

		curTran->name=tname.substr(0,nPrefix);
		curTran->channel=tname.substr(nPrefix,tname.length()-nPrefix);

		if(dMode>=GATING_SET_LEVEL)
				cout<<"parsing calibrationTable:"<<curTran->name<<":"<<curTran->channel<<endl;

//		t.biExpDecades=atof(calTblNode.getProperty("biexponentialDecades").c_str());
//		t.biExpNegDecades=atof(calTblNode.getProperty("biexponentialNegDecades").c_str());
//		t.w=atof(calTblNode.getProperty("biexponentialWidth").c_str());

		string sTbl=calTblNode.getContent();
		/*
		 * parse the stream to x,y double arrays
		 */
		valarray<double> tbl(toArray(sTbl));
		unsigned nX=tbl.size()/2;


		t->init(nX);

		t->y=tbl[slice(0,nX,2)];
		t->x=tbl[slice(1,nX,2)];

		/*
		 * output to text for testing
		 */
//		ofstream xOutput("../output/c++/x.csv");
//		ofstream yOutput("../output/c++/y.csv");
//		for(unsigned i=0;i<nX;i++)
//		{
//			xOutput<<t->x[i]<<",";
//			yOutput<<t->y[i]<<",";
//		}


		if(dMode>=GATING_SET_LEVEL)
			cout<<"spline interpolating..."<<curTran->name<<endl;

		t->interpolate();

		curTran->calTbl=t;

		res.push_back(curTran);

	}

	xmlXPathFreeObject(result);
	xmlXPathFreeContext(context);
	return res;
}
compensation macFlowJoWorkspace::getCompensation(wsSampleNode sampleNode)
{
	compensation comp;
	comp.cid=sampleNode.getProperty("compensationID");

	/*
	 * -1:Acquisition-defined,to be computed from data
	 * -2:None
	 * empty:data is compensated already,spillover matrix can be read from keyword node or empty
	 * other:the spillover matrix is stored at special compensation node,
	 * 			and this cid serves as id to index that node. in pc version, we observe it is also stored at curent
	 * 			sampleNode,to keep the parsing consistent,we still look for it from the special compensation node within the context of xml root
	 */
	if(comp.cid.compare("-1")==0)
	{
		comp.comment="Acquisition-defined";
		comp.prefix="<";
		comp.suffix=">";
	}
	else if(comp.cid.compare("-2")==0)
				comp.comment="none";
	else if(comp.cid.empty())
				throw(domain_error("empty cid not supported yet!"));
	else
	{
		/*
		 * look for CompensationMatrix nodes
		 */
		string path="/Workspace/CompensationMatrices/CompensationMatrix";
		xmlXPathObjectPtr resMat=sampleNode.xpath(path);

		if(resMat->nodesetval->nodeNr<=0)
			throw(domain_error("no CompensationMatrix found!"));
		/*
		 * look for the particular CompensationMatrix for current sampleNode by cid
		 */
		unsigned short cid=atoi(comp.cid.c_str());
		wsNode curMatNode(resMat->nodesetval->nodeTab[cid]);

		xmlXPathFreeObject(resMat);
		comp.prefix=curMatNode.getProperty("prefix");
		comp.suffix=curMatNode.getProperty("suffix");

		xmlXPathObjectPtr resX=curMatNode.xpathInNode("Channel");
		unsigned nX=resX->nodesetval->nodeNr;
		for(unsigned i=0;i<nX;i++)
		{
			wsNode curMarkerNode_X(resX->nodesetval->nodeTab[i]);
			comp.marker.push_back(curMarkerNode_X.getProperty("name"));
			xmlXPathObjectPtr resY=curMarkerNode_X.xpathInNode("ChannelValue");
			unsigned nY=resY->nodesetval->nodeNr;
			if(nX!=nY)
				throw(domain_error("not the same x,y dimensions in spillover matrix!"));
			for(unsigned j=0;j<nY;j++)
			{
				wsNode curMarkerNode_Y(resY->nodesetval->nodeTab[j]);
				string sValue=curMarkerNode_Y.getProperty("value");
				comp.spillOver.push_back(atof(sValue.c_str()));
			}
			xmlXPathFreeObject(resY);
		}
		xmlXPathFreeObject(resX);

	}

	if(dMode>=GATING_HIERARCHY_LEVEL)
			cout<<"parsing compensation matrix.."<<endl;
	return comp;
}


compensation winFlowJoWorkspace::getCompensation(wsSampleNode sampleNode)
{
	compensation comp;

	xmlXPathObjectPtr res=sampleNode.xpathInNode("*[local-name()='spilloverMatrix']");
	if(res->nodesetval->nodeNr!=1)
		throw(domain_error("not valid compensation node!"));

	wsNode node(res->nodesetval->nodeTab[0]);
	xmlXPathFreeObject(res);

	comp.cid=node.getProperty("id");
	comp.prefix=node.getProperty("prefix");
	/*
	 * -1:Acquisition-defined,to be computed from data
	 * -2:None
	 * empty:data is compensated already,spillover matrix can be read from keyword node or empty
	 * other:the spillover matrix is stored at special compensation node,
	 * 			and this cid serves as id to index that node. in pc version, we observe it is also stored at curent
	 * 			sampleNode,to keep the parsing consistent,we still look for it from the special compensation node within the context of xml root
	 */
	if(comp.cid.compare("-1")==0)
	{
		comp.comment="Acquisition-defined";
		comp.prefix="Comp-";
	}
	else if(comp.cid.compare("-2")==0)
		comp.comment="none";
	else if(comp.cid.empty())
		throw(domain_error("empty cid not supported yet!"));
	else
	{
		string path="/Workspace/CompensationEditor/Compensation[@name='"+comp.cid+"']/*[local-name()='spilloverMatrix']/*[local-name()='spillover']";
//			cout<<path<<endl;
		xmlXPathObjectPtr resX=node.xpath(path);
		unsigned nX=resX->nodesetval->nodeNr;
		for(unsigned i=0;i<nX;i++)
		{
			wsNode curMarkerNode_X(resX->nodesetval->nodeTab[i]);
			comp.marker.push_back(curMarkerNode_X.getProperty("parameter"));
			xmlXPathObjectPtr resY=curMarkerNode_X.xpathInNode("*[local-name()='coefficient']");
			unsigned nY=resY->nodesetval->nodeNr;
			if(nX!=nY)
				throw(domain_error("not the same x,y dimensions in spillover matrix!"));
			for(unsigned j=0;j<nY;j++)
			{
				wsNode curMarkerNode_Y(resY->nodesetval->nodeTab[j]);
				string sValue=curMarkerNode_Y.getProperty("value");
				comp.spillOver.push_back(atof(sValue.c_str()));
			}
			xmlXPathFreeObject(resY);
		}
		xmlXPathFreeObject(resX);

	}
	if(dMode>=GATING_HIERARCHY_LEVEL)
			cout<<"parsing compensation matrix.."<<endl;
	return comp;
}

//xquery the "SampleNode" within "sample" context
wsRootNode flowJoWorkspace::getRoot(wsSampleNode sample)
{
//	cout<<"parsing root node"<<endl;
	xmlXPathObjectPtr res=sample.xpathInNode(nodePath.sampleNode);
	wsRootNode node(res->nodesetval->nodeTab[0]);
	xmlXPathFreeObject(res);
//	cout<<nodePath.sampleNode<<endl;
	return node;
}


wsPopNodeSet flowJoWorkspace::getSubPop(wsNode * node)
{

	xmlXPathObjectPtr res=node->xpathInNode(nodePath.popNode);
	int nChildren=res->nodesetval->nodeNr;
//	wsPopNodeSet childenNodes(res->nodesetval->nodeTab,nChildren);
	wsPopNodeSet childenNodes;
	for(int i=0;i<nChildren;i++)
	{
		childenNodes.push_back(wsPopNode(res->nodesetval->nodeTab[i]));
	}

	xmlXPathFreeObject(res);

	return childenNodes;

}

polygonGate* winFlowJoWorkspace::getGate(wsEllipseGateNode & node){
	throw(domain_error("ellipse gate is not supported yet"));
	return NULL;
}
polygonGate* winFlowJoWorkspace::getGate(wsPolyGateNode & node){
			polygonGate * gate=new polygonGate();
			//get the negate flag
			gate->isNegate=node.getProperty("eventsInside")=="0";

			//TODO:get parameter name(make sure the the order of x,y are correct)
			xmlXPathObjectPtr resPara=node.xpathInNode("*[local-name()='dimension']/*[local-name()='parameter']");
			int nParam=resPara->nodesetval->nodeNr;
			if(nParam!=2)
			{
//				cout<<"the dimension of the polygon gate:"<<nParam<<" is invalid!"<<endl;
				throw(domain_error("invalid dimension of the polygon gate!"));
			}
			for(int i=0;i<nParam;i++)
			{
				wsNode curPNode(resPara->nodesetval->nodeTab[i]);
				string curParam=curPNode.getProperty("name");
				gate->params.push_back(curParam);
			}
			xmlXPathFreeObject(resPara);

			//get vertices
			xmlXPathObjectPtr resVert=node.xpathInNode("*[local-name()='vertex']");
			for(int i=0;i<resVert->nodesetval->nodeNr;i++)
			{
				wsNode curVNode(resVert->nodesetval->nodeTab[i]);

				/*for each vertice node
				**get one pair of coordinates
				*/
				xmlXPathObjectPtr resCoord=curVNode.xpathInNode("*[local-name()='coordinate']");

				xmlNodeSetPtr nodeSet=resCoord->nodesetval;
				int nCoord=nodeSet->nodeNr;
				if(nCoord!=2)
				{
//					cout<<"the number of coordinates:"<<nCoord<<" is invalid!"<<endl;
					throw(domain_error("invalid  number of coordinates!"));
				}
				//get the coordinates values from the property of respective node
				coordinate pCoord;
	//			wsNode xcord(nodeSet->nodeTab[0]);
	//			string sXcord=xcord.getProperty("value");
	//			pCoord.first=atof(sXcord.c_str());
				pCoord.x=atof(wsNode(nodeSet->nodeTab[0]).getProperty("value").c_str());
				pCoord.y=atof(wsNode(nodeSet->nodeTab[1]).getProperty("value").c_str());
				//and push to the vertices vector of the gate object
				gate->vertices.push_back(pCoord);

				xmlXPathFreeObject(resCoord);
			}
			xmlXPathFreeObject(resVert);
			return gate;
}
polygonGate* winFlowJoWorkspace::getGate(wsRectGateNode & node){
			polygonGate * g=new polygonGate();
			//get the negate flag
			g->isNegate=node.getProperty("eventsInside")=="0";

			//get parameter name
			xmlXPathObjectPtr resPara=node.xpathInNode("*[local-name()='dimension']");
			int nParam=resPara->nodesetval->nodeNr;
			if(nParam!=2)
			{
//				cout<<"the dimension of the rectangle gate:"<<nParam<<" is invalid!"<<endl;
				throw(domain_error("invalid  dimension of the rectangle gate!"));
			}
			vector<pRange> r(2);
			for(int i=0;i<nParam;i++)
			{
				wsNode curPNode(resPara->nodesetval->nodeTab[i]);

				//get coordinates from properties

				string sMin=curPNode.getProperty("min");
				r.at(i).min=sMin.empty()?numeric_limits<double>::min():atof(sMin.c_str());

				string sMax=curPNode.getProperty("max");
				r.at(i).max=sMax.empty()?numeric_limits<double>::max():atof(sMax.c_str());

				//get parameter name from the children node
				xmlXPathObjectPtr resPName=curPNode.xpathInNode("*[local-name()='parameter']");
				r.at(i).name=wsNode(resPName->nodesetval->nodeTab[0]).getProperty("name");
				xmlXPathFreeObject(resPName);


			}
			/*
			 * convert pRanges to polygon data structure
			 */
			g->params.push_back(r.at(0).name);//x
			g->params.push_back(r.at(1).name);//y

			coordinate lb,lt,rb,rt;//left bottom,left top,right bottom,right top
			lb.x=r.at(0).min;
			lb.y=r.at(1).min;

			lt.x=r.at(0).min;
			lt.y=r.at(1).max;

			rb.x=r.at(0).max;
			rb.y=r.at(1).min;

			rt.x=r.at(0).max;
			rt.y=r.at(1).max;

			g->vertices.push_back(lb);
			g->vertices.push_back(lt);
			g->vertices.push_back(rb);
			g->vertices.push_back(rt);

			xmlXPathFreeObject(resPara);
			return g;
}
gate* winFlowJoWorkspace::getGate(wsPopNode & node){


	xmlXPathObjectPtr resGate=node.xpathInNode("Gate/*");
	wsNode gNode(resGate->nodesetval->nodeTab[0]);
	xmlXPathFreeObject(resGate);
	const xmlChar * gateType=gNode.thisNode->name;
	if(xmlStrEqual(gateType,(const xmlChar *)"PolygonGate"))
	{
		wsPolyGateNode pGNode(gNode.thisNode);
		if(dMode>=GATE_LEVEL)
			cout<<"parsing PolygonGate.."<<endl;
		return(getGate(pGNode));

	}
	else if(xmlStrEqual(gateType,(const xmlChar *)"RectangleGate"))
	{
		wsRectGateNode rGNode(gNode.thisNode);
		if(dMode>=GATE_LEVEL)
			cout<<"parsing RectangleGate.."<<endl;
		return(getGate(rGNode));
	}
	else
	{
//		cout<<"gate type: "<<gateType<<" is not supported!"<<endl;
		throw(domain_error("invalid  gate type!"));
	}

}

rangegate* macFlowJoWorkspace::getGate(wsRangeGateNode & node){
	/*
	 * using the same routine of polygon gate to parse ellipse
	 */
	wsPolyGateNode pGNode(node.thisNode);
	polygonGate * g1=getGate(pGNode);
	/*
	 * convert to the rangeGate data structure after the preliminary parsing step
	 */
	rangegate *g=new rangegate();

	if(g1->vertices.size()!=2)
			throw(domain_error("fail to convert to Range Gate since the vertices number is not 2!"));


	g->param.name=g1->params.at(0);
	coordinate p1=g1->vertices.at(0);
	coordinate p2=g1->vertices.at(1);
	if(p1.x!=p2.x)
	{
		g->param.min=min(p1.x,p2.x);
		g->param.max=max(p1.x,p2.x);
	}
	else
	{
		g->param.min=min(p1.y,p2.y);
		g->param.max=max(p1.y,p2.y);
	}
	delete g1;
	return(g);

}

bool compare_x(coordinate i, coordinate j) { return i.x<j.x; }
bool compare_y(coordinate i, coordinate j) { return i.y<j.y; }


polygonGate* macFlowJoWorkspace::getGate(wsEllipseGateNode & node){
	/*
	 * using the same routine of polygon gate to parse ellipse
	 */
	wsPolyGateNode pGNode(node.thisNode);
	polygonGate * g=getGate(pGNode);
	/*
	 * using 4 vertices to fit polygon points
	 */
	vector<coordinate> v=g->vertices;
	g->vertices.clear();//reset the vertices

	coordinate R=*max_element(v.begin(),v.end(),compare_x);
	coordinate L=*min_element(v.begin(),v.end(),compare_x);

	coordinate T=*max_element(v.begin(),v.end(),compare_y);
	coordinate B=*min_element(v.begin(),v.end(),compare_y);

	coordinate E;
	E.x=hypot(L.x-R.x,L.y-R.y)/2;
	E.y=hypot(T.x-B.x,T.y-B.y)/2;

	double phi=tan((R.y-L.y)/(R.x-L.x));
	double CY=(B.y+T.y)/2;
	double CX=(R.x+L.x)/2;


	double delta=2*PI/100;
	for(unsigned short i=0;i<100;i++)
	{
		double S=i*delta;
		coordinate p;
		p.x=CX+E.x*cos(S)*cos(phi)-E.y*sin(S)*sin(phi);
		p.y=CY+E.x*cos(S)*sin(phi)+E.y*sin(S)*cos(phi);
		g->vertices.push_back(p);
	}

	return(g);

}
/*
 * TODO:query gate node and param node by name instead of by positions
 */
polygonGate* macFlowJoWorkspace::getGate(wsPolyGateNode & node){
			polygonGate * gate=new polygonGate();
			/*
			 * re-fetch the children node from the current pop node
			 */
			xmlXPathObjectPtr resGate=node.xpathInNode("PolygonGate/*");
//			wsNode pNode(resGate->nodesetval->nodeTab[0]);//gate dimensions
			wsNode gNode(resGate->nodesetval->nodeTab[2]);//gate type and vertices
			xmlXPathFreeObject(resGate);

			//get the negate flag
			gate->isNegate=!gNode.getProperty("negated").empty();

			//get parameter name
//			xmlXPathObjectPtr resPara=pNode.xpathInNode("StringArray/String");
//			int nParam=resPara->nodesetval->nodeNr;
//			if(nParam!=2)
//			{
////				cout<<"the dimension of the polygon gate:"<<nParam<<" is invalid!"<<endl;
//				throw(domain_error("invalid dimension of the polygon gate!"));
//			}
//			for(int i=0;i<nParam;i++)
//			{
//				wsNode curPNode(resPara->nodesetval->nodeTab[i]);
//				string curParam=curPNode.getContent();
//				gate->params.push_back(curParam);
//			}
//			xmlXPathFreeObject(resPara);


			string xAxis=gNode.getProperty("xAxisName");
			gate->params.push_back(xAxis);
			string yAxis=gNode.getProperty("yAxisName");
			if(!yAxis.empty())
				gate->params.push_back(yAxis);

			//get vertices
			xmlXPathObjectPtr resVert=gNode.xpathInNode("Polygon/Vertex");
			for(int i=0;i<resVert->nodesetval->nodeNr;i++)
			{
				wsNode curVNode(resVert->nodesetval->nodeTab[i]);

				/*for each vertice node
				**get one pair of coordinates
				*/

				//get the coordinates values from the property
				coordinate pCoord;
				pCoord.x=atof(curVNode.getProperty("x").c_str());
				pCoord.y=atof(curVNode.getProperty("y").c_str());
				//and push to the vertices vector of the gate object
				gate->vertices.push_back(pCoord);

			}
			xmlXPathFreeObject(resVert);
			return gate;
}



gate* macFlowJoWorkspace::getGate(wsPopNode & node){


	xmlXPathObjectPtr resGate=node.xpathInNode("PolygonGate/*");
	if(resGate->nodesetval->nodeNr!=3)
	{
		xmlXPathFreeObject(resGate);
		throw(domain_error("invalid gate node(less than 3 children)"));
	}
//	wsNode pNode(resGate->nodesetval->nodeTab[0]);//gate dimensions
	wsNode gNode(resGate->nodesetval->nodeTab[2]);//gate type and vertices
	xmlXPathFreeObject(resGate);


	const xmlChar * gateType=gNode.thisNode->name;
	if(xmlStrEqual(gateType,(const xmlChar *)"Polygon"))
	{
		wsPolyGateNode pGNode(node.thisNode);
		if(dMode>=GATE_LEVEL)
			cout<<"parsing PolygonGate.."<<endl;
		return(getGate(pGNode));
	}
	else if(xmlStrEqual(gateType,(const xmlChar *)"PolyRect"))//parse rect as polygon gate
	{
		wsPolyGateNode pGNode(node.thisNode);
		if(dMode>=GATE_LEVEL)
			cout<<"parsing RectangleGate.."<<endl;
		return(getGate(pGNode));
	}
	else if(xmlStrEqual(gateType,(const xmlChar *)"Ellipse"))
	{
		wsEllipseGateNode eGNode(node.thisNode);
		if(dMode>=GATE_LEVEL)
			cout<<"parsing EllipseGate.."<<endl;
		return(getGate(eGNode));
	}
	else if(xmlStrEqual(gateType,(const xmlChar *)"Range"))
	{
		wsRangeGateNode rnGNode(node.thisNode);

		if(dMode>=GATE_LEVEL)
			cout<<"parsing RangeGate.."<<endl;
		return(getGate(rnGNode));
	}
	else
	{
//		cout<<"gate type: "<<gateType<<" is not supported!"<<endl;
		throw(domain_error("invalid  gate type!"));
	}
	return NULL;
}
/*
 *Note: nodeProperties is dynamically allocated and up to caller to free it
 */
nodeProperties* flowJoWorkspace::to_popNode(wsRootNode & node){

	nodeProperties * pNode=new nodeProperties;

	pNode->setName(node.getProperty("name").c_str());

	pNode->fjStats["count"]=atoi(node.getProperty("count").c_str());

	pNode->dMode=dMode;
	return pNode;
}

nodeProperties* flowJoWorkspace::to_popNode(wsPopNode &node,bool isParseGate=false){


	nodeProperties * pNode=new nodeProperties;
	//add pop name
	pNode->setName(node.getProperty("name").c_str());

	if(dMode>=POPULATION_LEVEL)
			cout<<"parse the population Node:"<<pNode->getName()<<endl;
	//add pop counts
	pNode->fjStats["count"]=atoi(node.getProperty("count").c_str());


	try
	{
		if(isParseGate)pNode->setGate(getGate(node));
	}
	catch (int e) {
		cout<<"extracting gate failed:"<<pNode->getName()<<endl;
	}
	pNode->dMode=dMode;
	return pNode;
}
