#include <fstream>
#include <ctime>

std::ifstream f("calendar.in");
std::ofstream g("calendar.out");

int zi, luna, an;
std::string zile[] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
std::string luni[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
unsigned int nr_zile[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 
unsigned int luna_t[6][7];

unsigned int reverseday(unsigned int a){
	unsigned int b = a;
	if(b == 0)
		b = 7;
	b--;
	return b;
}

unsigned int getweekday(int dd, int mm, int yy){
	std::tm time_in = {0, 0, 0, dd, mm, yy - 1900};
	std::time_t time_temp = std::mktime(&time_in);
	const std::tm* time_out = std::localtime(&time_temp);
	
	return time_out->tm_wday;
}

bool leapyear(unsigned int year){
	if(year % 4 == 0)
		if(year % 100 == 0)
			if(year % 400 == 0) return true;
			else return false;
		else return true;
	else return false;
    
}

unsigned int getprimsapt(unsigned int st, int ln, int an, unsigned int month[6][7]){
	if(ln - 1 < 0)
		ln = 12;
	ln--;
	unsigned int v = nr_zile[ln];
	if(leapyear(an) && ln == 1)
		v++;
	
	unsigned int k = 0;
	for(int i = st - 1; i >= 0; i--){ //daca e unsigned face overflow si inca e mai mare decat 0
		month[0][i] = v;//, g << month[0][i] << ' ';
		v--;
	}
	for(unsigned int i = st; i < 7; i++){
		k++;
		month[0][i] = k;
		//g << month[0][i] << ' ';
	}
	//g << '\n'
	return k;
}

int main()
{
    f >> luna >> an;
    luna--;
    g << luni[luna] << ' ' << an << '\n';
    unsigned int zi_t = getweekday(zi, luna, an);
    unsigned int zi_a = zi_t;
    if(zi != 1)
        zi_a = getweekday(1, luna, an);
    zi_a = reverseday(zi_a);
    zi_t = reverseday(zi_t);
    
    unsigned int nr = nr_zile[luna];
    if(leapyear(an) && luna == 1)
        nr++;
    
    unsigned int k = getprimsapt(zi_a, luna, an, luna_t);
    unsigned int l = 0;
    for(unsigned int i = 1; i <= 5; i++){
        for(unsigned int j = 0; j < 7; j++){
            if(k < nr){
                k++;
                luna_t[i][j] = k;
            } else {
                l++;
                luna_t[i][j] = l;
            }
        }
    }
    
    for(int i = 0; i < 7; i++)
        g << zile[i] << ' ';
    g << '\n';
    
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            if(luna_t[i][j] < 10)
                g << luna_t[i][j] << "   ";
            else
                g << luna_t[i][j] << "  ";
            luna_t[i][j] = 0;
        }
        g << '\n';
    }
    g << '\n';
    
    return 0;
}
