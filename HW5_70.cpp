#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <stdio.h> 
#include <algorithm>
#include <list>
#include <sstream>
#include <stack>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <queue>

using namespace std;

int vc,hc;//limit capacity

class Net{
	public:
	pair<int,int> s;
	pair<int,int> t;
	int mamd;
	string net_name;
	int net_id;
	int lock;
	vector<pair<int,int> > path;
};
class Node{
	public:
	pair<int,int> cor;
	int parent;
	int cost;
};
class CTest
{
public:

	pair<int,int> cor;
	int index;
    int cost;
};


class Grid{
	public:
	stack<int> hc;
	stack<int> vc;
};
struct cmp1
{
    bool operator()(CTest a, CTest b)
    {
        int costa = a.cost;
        int costb = b.cost;
        //return a->_distance > b->_distance;
        return costa > costb;
    }
};
void test(vector<Net> net)
{
	vector<Net>::iterator iter;
	for(iter=net.begin();iter!=net.end();iter++)
	{
		//cout<<(*iter).net_name<<endl;
	}
}
/*void test(vector<Net> net)
{
	list<Net>::iterator iter;
	for(iter=net.begin();iter!=net.end();iter++)
	{
	//	//cout<<(*iter).mamd<<"   "<<(*iter).net_id<<"   "<<(*iter).net_name<<endl;
		if((*iter).path.size()>0)
		{
			//cout<<(*iter).path[0]<<"     "<<(*iter).path[1]<<endl;
		}
	//	//cout<<(*iter).path.size()<<endl;
	}
}//*/
void test_ca(vector<stack<int> > h_ca,vector<stack<int> > v_ca,int wx,int hy)
{
	int a,b;
	a=b=0;
	for(int i=0;i<h_ca.size();i++)
	{
		//cout<<i<<" : "<<h_ca[i].size();
		if(h_ca[i].size()>hc)
		{
			//cout<<"<<<<<<<<<<<overflow<<<<<<<<"<<endl;
			a++;
		}
		else
			cout<<endl;
	}
	for(int i=0;i<v_ca.size();i++)
	{
		//cout<<i<<" : "<<v_ca[i].size();
		if(v_ca[i].size()>vc)
		{
			//cout<<"<<<<<<<<<<<overflow<<<<<<<<"<<endl;
			b++;
		}
		else
			cout<<endl;
	}
	//cout<<"H overflow: "<<a<<"     V overflow: "<<b<<endl;
}
int vindex(int wx,int x, int y)
{
	return y*wx+x;
}
int hindex(int wx,int x, int y)
{
	return y*(wx-1)+x;
}
void route(vector<Net> &net,vector<stack<int> > &h_ca,vector<stack<int> > &v_ca,int wx,int hy,vector<vector<int> > &order_of_net)
{
	vector<Net>::iterator iter;//y*(wx-1)+x(the left)=index h_ca[index] y*wx+x(the left)=index v_ca[index]
	int count=0;
	int start,end;
	for(int i=0;i<order_of_net.size();i++)
	{
		int ind;
		for(int j=0;j<order_of_net[i].size();j++)
		{
			int tem_index=order_of_net[i][j];
			count=0;
			int px,py;//select the node
			int dx,dy;//direct tag
			int au,ad,al,ar;
			int p_index;//path_index for path;
			au=ad=al=ar=1;
			Node tnode;
			CTest tem;
			priority_queue <CTest,vector<CTest>,cmp1 > p_greater;
			vector<pair<int,int> > real_path;
			vector<pair<int,int> > close;
			vector<Node> path;
			cout<<"ID: "<<net[tem_index].net_id<<endl;
			start=clock();
			while(1)
			{  
				int up,down,right,left,md,td;
				int cx,cy;
				int ctrv=0,ctrh=0;
				int hcost,vcost;
				pair<int,int> sel;
				vector<pair<int,int> >::iterator it;
				up=down=right=left=INT_MAX;//A* cost value

				if(count==0)
				{
					cx=net[tem_index].s.first;
					cy=net[tem_index].s.second;
					tnode.cor=make_pair(cx,cy);
					tnode.parent=0;
					tnode.cost=0;
					path.push_back(tnode);
					p_index=count;
					close.push_back(tnode.cor);
				}
				else
				{
					cx=px;
					cy=py;
				}
				
				for(it=close.begin();it!=close.end();it++)
				{
					if(cx == (*it).first && cy+1 == (*it).second)
					{
						au=0;
					}
					if(cx == (*it).first && cy-1 == (*it).second)
					{
						ad=0;
					}
					if(cx+1 == (*it).first && cy == (*it).second)
					{
						ar=0;
					}
					if(cx-1 == (*it).first && cy == (*it).second)
					{
						al=0;
					}
				}//檢查有無造訪過的點
				
				if(cy+1 >= 0 && au==1 && cy+1 < hy)
				{
					md=abs((cy+1)-(net[tem_index].t.second))+abs(cx - net[tem_index].t.first);
					td=vindex(wx,cx,cy);
					if(v_ca[td].size() >= INT_MAX)
						up=md+10000;
					else
					{
						up=md+v_ca[td].size();
						
					}
					tnode.cor=make_pair(cx,cy+1);
					tnode.parent=p_index;
					tnode.cost=up;
					path.push_back(tnode);
					count++;
					tem.index=count;
					tem.cost=up;
					tem.cor=make_pair(cx,cy+1);
					p_greater.push(tem);
					
				}
				if(cy-1 >= 0 && ad==1)
				{
					md=abs((cy-1)-(net[tem_index].t.second))+abs(cx - net[tem_index].t.first);
					td=vindex(wx,cx,cy-1);
					if(v_ca[td].size() >= INT_MAX)
						down=md+10000;
					else
					{
						down=md+v_ca[td].size();
				
					}
					tnode.cor=make_pair(cx,cy-1);
					tnode.parent=p_index;
					tnode.cost=down;
					path.push_back(tnode);
					count++;
					tem.index=count;
					tem.cost=down;
					tem.cor=make_pair(cx,cy-1);
					p_greater.push(tem);
				}

				if(cx+1 >= 0 && ar==1 && cx+1 < wx)
				{
					md=abs(cy-net[tem_index].t.second)+abs((cx+1) - net[tem_index].t.first);
					td=hindex(wx,cx,cy);
					if(h_ca[td].size() >= INT_MAX)
						right=md+10000;
					else
					{
						right=md+h_ca[td].size();
						
					}
					tnode.cor=make_pair(cx+1,cy);
					tnode.parent=p_index;
					tnode.cost=right;
					path.push_back(tnode);
					count++;
					tem.index=count;
					tem.cost=right;
					tem.cor=make_pair(cx+1,cy);
					p_greater.push(tem);
					
				}
				if(cx-1 >= 0 && al==1)
				{
					md=abs(cy-net[tem_index].t.second)+abs((cx-1) - net[tem_index].t.first);
					td=hindex(wx,cx-1,cy);
					if(h_ca[td].size() >= INT_MAX)
						left=md+10000;
					else
					{
						left=md+h_ca[td].size();
						
					}
					tnode.cor=make_pair(cx-1,cy);
					tnode.parent=p_index;
					tnode.cost=left;
					path.push_back(tnode);
					count++;
					tem.index=count;
					tem.cost=left;
					tem.cor=make_pair(cx-1,cy);
					p_greater.push(tem);
				}
				
				tem=p_greater.top();//x=tem.cor.first;y=tem.cor.second;
				p_greater.pop();
				p_index=tem.index;
				px=tem.cor.first;
				py=tem.cor.second;
				close.push_back(tem.cor);
				au=ad=al=ar=1;
				if(px == net[tem_index].t.first && py ==net[tem_index].t.second)
				{
					while(1)
					{
						real_path.push_back(make_pair(path[p_index].cor.first,path[p_index].cor.second));
						p_index=path[p_index].parent;
						if(p_index == 0)
						{
							real_path.push_back(make_pair(path[p_index].cor.first,path[p_index].cor.second));
							break;
						}
					}
					break;
				}	
			}
			end=clock();
			cout<<"ID: "<<net[tem_index].net_id<<"  time: "<<(end-start)/CLOCKS_PER_SEC<<endl;
			count=0;//reset 
			int change;
			vector<pair<int,int> >::reverse_iterator ip;
			ip=real_path.rbegin();
			net[tem_index].path.push_back(make_pair((*ip).first,(*ip).second));//起始點
			
			if((*ip).first==(*(ip+1)).first)
				change=1;
			else
				change=0;
			for(ip=real_path.rbegin();ip!=real_path.rend();ip++)
			{
				//cout<<(*ip).first<<"     "<<(*ip).second<<"--------------";
				//cout<<(*(ip+1)).first<<"     "<<(*(ip+1)).second<<"  xxxx"<<change<<endl;
//				//cout<<net[tem_index].t.first<<"     "<<net[tem_index].t.second<<endl; 
				int ttx,tty;
				if((*ip).first==(*(ip+1)).first)
				{
					if((*ip).second>(*(ip+1)).second)
					{
						tty=(*(ip+1)).second;
					}
					else
					{
						tty=(*ip).second;
					}
					
					ttx=(*ip).first;
					ind=vindex(wx,ttx,tty);
					v_ca[ind].push(net[tem_index].net_id);
					if(change!=1)
					{
						net[tem_index].path.push_back(make_pair((*ip).first,(*ip).second));
						change=1;
					}
					
				}
				else
				{
					if((*ip).first>(*(ip+1)).first)
					{
						ttx=(*(ip+1)).first;
					}
					else
					{
						ttx=(*ip).first;
					}
					tty=(*ip).second;
					ind=hindex(wx,ttx,tty);
					h_ca[ind].push(net[tem_index].net_id);
					if(change!=0)
					{
						net[tem_index].path.push_back(make_pair((*ip).first,(*ip).second));//將轉彎的點存下來
						change=0;
					}
				}
				if( (*(ip+1)).first == net[tem_index].t.first && (*(ip+1)).second == net[tem_index].t.second )
				{
					net[tem_index].path.push_back(make_pair((*(ip+1)).first,(*(ip+1)).second));//終點
					//cout<<"FINAL<<<<<<<"<<endl;
					break;
				}
					
				
			}
			
			//update v h capacity
			
		}
	}
//	test(net);
//	//cout<<count<<endl;
//	test_ca(h_ca,v_ca,wx,hy);
}

/*
void sort(vector<Net> &net)
{
	list<Net>::iterator iter;
	vector<Net> tem;
	for(iter=net.begin();iter!=net.end();iter++)
	{
		if(iter==net.begin())
		{
			tem.push_back(*iter);
		}
		else
		{
			list<Net>::iterator it;
			int count=0;
			for(it=tem.begin();it!=tem.end();it++)
			{
				if((*iter).mamd <= (*it).mamd)
				{
					tem.insert(it,*iter);
					break;
				}
				count++;
				if(count == tem.size())
				{
					tem.push_back(*iter);
					break;
				}
			}
		}
	}
	net=tem;
//	test(net);
}//*/

void output_file(vector<Net> &net,string file_name)
{
	vector<Net>::iterator iter;
	vector<pair<int,int> >::iterator it;
	fstream w_file;
	//cout<<"I'm here"<<endl;
	string file="../output/"+file_name;
	//cout<<file<<endl;
	w_file.open(file.c_str(),ios::out);
	for(iter=net.begin();iter!=net.end();iter++)
	{
		//cout<<"----"<<endl;
		int px,py;
		w_file<<(*iter).net_name<<" "<<(*iter).net_id<<endl;
		//cout<<(*iter).net_name<<" "<<(*iter).net_id<<endl;
		//cout<<(*iter).path.size()<<endl;
		w_file<<"("<<(*iter).path[0].first<<", "<<(*iter).path[0].second<<", 1)";
		//cout<<"("<<(*iter).path[0].first<<", "<<(*iter).path[0].second<<", 1)";
		for(it=(*iter).path.begin()+1;it!=(*iter).path.end();it++)
		{
			
			w_file<<"-("<<(*it).first<<", "<<(*it).second<<", 1)"<<endl;
			//cout<<"-("<<(*it).first<<", "<<(*it).second<<", 1)"<<endl;
			if((it+1) == (*iter).path.end() )
			{
				break;
			}
			else
			{
				w_file<<"("<<(*it).first<<", "<<(*it).second<<", 1)";
				//cout<<"("<<(*it).first<<", "<<(*it).second<<", 1)";
			}
		}
		w_file<<"!"<<endl;
	}
	w_file.close();
}
vector<vector<int> > ocompute(vector<vector<int> > &graph,vector<Net> &net, int bigmd)
{
	vector<vector<int> > index_order;
	vector<int> tem;
	vector<Net>::iterator iter;
	//cout<<bigmd<<endl;
	for(int i=0;i<=bigmd;i++)
	{
		index_order.push_back(tem);//0不算
	}
	
	for(int i=0;i<net.size();i++)
	{
		int md;
		md=net[i].mamd;
		index_order[md].push_back(i);
	}
/*	for(int i=0;i<index_order.size();i++)
	{
		for(int j=0;j<index_order[i].size();j++)
		{
			int x;
			x=index_order[i][j];
			//cout<<net[x].net_id<<"  ";
		}
		//cout<<endl;
	}//*/
	return index_order;
}

int main(int argc,char *argv[])
{
	int grid_x,grid_y;
//	int v_c,h_c;
	int net_num;
	
	string file_name;
	
	file_name="../testcase/ibm04.modified.txt";//change for argv[1];
	ifstream o_file;
	o_file.open(file_name.c_str());
	for(int i=0;i<4;i++)
	{
		string word,line;
		if(i==0)
		{
			getline(o_file,line);
			istringstream ss(line);
			ss>>word;
			ss>>word;
			grid_x=atoi(word.c_str());
//			//cout<<grid_x<<endl;
			ss>>word;
			grid_y=atoi(word.c_str());
//			//cout<<grid_y<<endl;
			
		}
		if(i==1)
		{
			getline(o_file,line);
			istringstream ss(line);
			ss>>word;
			ss>>word;
			ss>>word;
			vc=atoi(word.c_str());
//			//cout<<v_c<<endl;
		}
		if(i==2)
		{
			getline(o_file,line);
			istringstream ss(line);
			ss>>word;
			ss>>word;
			ss>>word;
			hc=atoi(word.c_str());
//			//cout<<h_c<<endl;
		}
		if(i==3)
		{
			getline(o_file,line);
			istringstream ss(line);
			ss>>word;
			ss>>word;
			ss>>word;
			net_num=atoi(word.c_str());
//			//cout<<net_num<<endl;
		}
		
	}
	
	vector<Net> net;
	Net t_item;
	int bigmd=0;
	vector<vector<int> > graph(grid_y, vector<int>(grid_x, 0));
	int big=0,small=0;
	for(int i=0;i<net_num;i++)
	{
		string name,word,line;
		int id;
		int s_x,s_y,t_x,t_y;
		int md;
		
		getline(o_file,line);
		istringstream ss(line);
		ss>>word;//name
		name=word;
		ss>>word;//id
		id=atoi(word.c_str());
		t_item.net_id=id;
		t_item.net_name=name;
		
		getline(o_file,line);
		istringstream ss1(line);
		ss1>>word;//s_x
		s_x=atoi(word.c_str());
		ss1>>word;//s_y
		s_y=atoi(word.c_str());
		t_item.s=make_pair(s_x,s_y);
		
		getline(o_file,line);
		istringstream ss2(line);
		ss2>>word;//t_x
		t_x=atoi(word.c_str());
		ss2>>word;//t_y
		t_y=atoi(word.c_str());
		t_item.t=make_pair(t_x,t_y);
		
		md=abs(s_x-t_x)+abs(s_y-t_y);
		graph[s_y][s_x]++;
		graph[t_y][t_x]++;
		t_item.mamd=md;
		t_item.lock=0;
		if(md>bigmd)
			bigmd=md;
	/*	if(md>7)
		{
			big++;
			net.push_back(t_item);
		}	
		else
		{
			small++;
			net.push_front(t_item);
		}//*/
		net.push_back(t_item);
			
	}
	vector<vector<int> > order_of_net;
	order_of_net=ocompute(graph,net,bigmd);
//	//cout<<net.size()<<endl;
/*	test(net);
	return 0;//*/
	//cout<<"BIG : "<<big<<" SMALL : "<<small<<endl;
	
	int num=(grid_x-1)*grid_y;
	vector<stack<int> > h_ca(num);
	num=grid_x*(grid_y-1);
	vector<stack<int> > v_ca(num);
//	//cout<<g_ca[0].hc.size()<<endl;

	route(net,h_ca,v_ca,grid_x,grid_y,order_of_net);
	string filen="test.txt";
	output_file(net,filen);
	
	
	return 0;
}