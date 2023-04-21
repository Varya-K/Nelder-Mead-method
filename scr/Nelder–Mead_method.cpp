#include "Nelder�Mead_method.h"
using namespace std;


NelderMead_method::NelderMead_method(Function* F, double Ecceptable_error) :f(F), ecceptable_error(Ecceptable_error) {}
NelderMead_method::NelderMead_method(Function* F, double Ecceptable_error, double Reflection, double Expansion, double Contraction, double Shrink) : 
	f(F), ecceptable_error(Ecceptable_error), reflection(Reflection), expansion(Expansion), contraction(Contraction), shrink(Shrink){}

Point NelderMead_method::Min() {
	
	int count = f->Dimension() + 1;
	Simplex S(count, count-1); //�������� ��������� �� n+1 ��������� �����
	
	int step = 0;

	double  st_deviation = S.standard_deviation(f); //����������� ���������� �������� ������� � ������ ���������. �������� ����������
	
	while (st_deviation > ecceptable_error) { //�������� ���������� � ������� ������������ ���������� �������� ������� � ������ ���������.
		step++;
		S.sort_simplex(f); //���������� ����� �� ����������� �������� �������
		Point Xh = S[count - 1]; //Xh - ����� � ���������� ��������� �������
		double Fh = f->Calculate(Xh);
		Point Xg = S[count - 2]; //Xg - ����� �� ��������� �� �������� ��������� �������
		double Fg = f->Calculate(Xg);
		Point Xl = S[0]; //Xl - ����� � ���������� ��������� �������
		double Fl = f->Calculate(Xl);
		
		Point X0 = S.centroid(count-1); //���������� "������ �������" ���� ����� �� ����������� Xh

		Point Xr = (1 + reflection) * X0 - reflection * Xh; // ��������� ����� Xh ������������ Xc � ������������ reflection
		double Fr = f->Calculate(Xr);

		Point Xe, Xc;

		//���� ����� Fr � ���� Fh, Fg, Fl
		if (Fr < Fl) { //������� ������� �����������, ������� ��������� ���
			Xe = (1 - expansion) * X0 + expansion * Xr; //���������� "����������"
			if (f->Calculate(Xe) < Fr)  S[count - 1] = Xe; //��������� �������� ����� �� ����� Xe: �������� Xh �������� Xe
			else S[count - 1] = Xr; //������������� ������� ������: �������� Xh �������� Xr
		}
		else if (Fr < Fg) S[count - 1] = Xr; //����� ����� Xr ��������: �������� Xh �������� Xr
		else {
			if (Fr < Fh) {
				S[count - 1] = Xr;
			}
			Xc = contraction * S[count-1] + (1 - contraction) * X0; //���������� "c�����", ��� S[S.Count()-1] = Xh
			if (f->Calculate(Xc) < f->Calculate(S[count-1])) S[count - 1] = Xc;
			else { //�������������� ����� ��������� ��������. ������ "���������� ������" ���������
				for (int j = 1; j < count; j++) {
					S[j] = Xl + shrink * (S[j] - Xl);
				}
			}
		}
		st_deviation = S.standard_deviation(f);

		if (should_be_printed) Print_middle(step, Xl, Xg, Xh, Xr, Xe, Xc, st_deviation);
	}

	Point Min_point = S[0]; //���������� ����� �� ������������� ��������� � ���������� ���������
	for (int i = 1; i < S.Count(); i++) {
		if (f->Calculate(Min_point) > f->Calculate(S[i])) Min_point = S[i];
	}
	return Min_point;
}

void NelderMead_method::Save(const char* file_name) {
	should_be_printed = true;
	
	ofstream filestr; //����� ��� ������ � ����
	filestr.open(file_name);

	streambuf* backup = cout.rdbuf();     // ����� ������ ������ cout

	streambuf* psbuf = filestr.rdbuf();        // �������� ����� ������ ����� 
	cout.rdbuf(psbuf);         // ��������� �� cout ����� ������ �����

	Print_begin_end();// ��������� �������, ������� ������� ���������

	cout.rdbuf(backup); //��������� �� cout ��� �� ����� ������ �������

	should_be_printed = false;

	cout << "The solution was successfully saved!" << endl;
}

void NelderMead_method::Print() {
	should_be_printed = true;
	Print_begin_end();
	should_be_printed = false;
}

void NelderMead_method::Print_begin_end() {

	cout<<"Ecceptable error = "<<ecceptable_error<<"\nCoefficients:\n Reflection = "<<reflection<<
		"\n Expansion = "<<expansion<<"\n Contraction = "<<contraction<<"\n Shrink = "<<shrink<<endl;
	cout<<"Step |     Xl     |     Fl     |     Xg     |     Fg     |     Xh     |     Fh     |     Xr     |     Fr     |     Xe     |     Fe     |     Xc     |     Fc     |standard deviation|\n";
	cout<<"-----|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------------|\n";
	
	Point res = Min();

	cout << "Result: " << f->Calculate(res) << "\nPoint:\n";
	for (int i = 0; i < res.Dimension(); i++) {
		cout<<" X"<<i+1<<" = "<<res[i]<<"\n";
	}
}

void NelderMead_method::Print_middle(int step, Point Xl, Point Xg, Point Xh, Point Xr, Point Xe, Point Xc, double st_deviation) {
	
	cout.setf(ios::fixed);
	cout<<" "<< setw(3) << step << " | " << setw(10) << setprecision(3) << Xl[0] << " | " << setw(10) << setprecision(3) << f->Calculate(Xl) << " | " <<
											setw(10) << setprecision(3) << Xg[0] << " | " << setw(10) << setprecision(3) << f->Calculate(Xg) << " | " <<
											setw(10) << setprecision(3) << Xh[0] << " | " << setw(10) << setprecision(3) << f->Calculate(Xh) << " | " <<
											setw(10) << setprecision(3) << Xr[0] << " | " << setw(10) << setprecision(3) << f->Calculate(Xr) << " | " ;
	if (Xe.Dimension()!=0) cout<< setw(10) << setprecision(3)<<Xe[0]<<" | "<< setw(10) << setprecision(3) << f->Calculate(Xe)<<" | ";
	else cout<<"    --     |     --     | ";
	if (Xc.Dimension() != 0) cout << setw(10) << setprecision(3) << Xc[0] << " | " << setw(10) << setprecision(3) << f->Calculate(Xc) << " | ";
	else cout<<"    --     |     --     | ";
	cout<< setw(16) << setprecision(5)<<st_deviation<<" |"<<endl;
	for (int j = 1; j < Xh.Dimension(); j++) {
		cout << "     | " << setw(10) << setprecision(3) << Xl[j] << " |            | " <<
							 setw(10) << setprecision(3) << Xg[j] << " |            | " <<
							 setw(10) << setprecision(3) << Xh[j] << " |            | " <<
							 setw(10) << setprecision(3) << Xr[j] << " |            | ";
		if (Xe.Dimension()!=0) cout << setw(10) << setprecision(3)<<Xe[j]<<" |            | ";
		else cout<<"           |            | ";
		if (Xc.Dimension() != 0) cout << setw(10) << setprecision(3) << Xc[j] << " |            | ";
		else cout << "           |            | ";
		cout<<("                 |\n");
	}
	cout<<"-----|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------------|\n";
}
