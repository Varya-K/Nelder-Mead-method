#include "Nelder�Mead_method.h"
#include <iostream>


Point NelderMead_method(Function* f, double ecceptable_error,
						double reflection, double expansion,
						double contraction, double shrink) {

	printf("Ecceptable error = %f\nCoefficients:\n Reflection = %f\n Expansion = %f\n Contraction = %f\n Shrink = %f\n", ecceptable_error, reflection, expansion, contraction, shrink);
	Simplex S(f->Dimensionality() + 1, f->Dimensionality()); //�������� ��������� �� n+1 �����
	S.rand_points(); //������ ��� ����� ����������

	int i = 0;
	printf("Step |     Xl     |     Fl     |     Xg     |     Fg     |     Xh     |     Fh     |     Xr     |     Fr     |     Xe     |     Fe     |     Xc     |     Fc     |standard deviation|\n");
	printf("-----|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------------|\n");

	double  st_deviation = S.standard_deviation(f); //����������� ���������� �������� ������� � ������ ���������. �������� ����������
	
	while (st_deviation > ecceptable_error) { //�������� ���������� � ������� ������������ ���������� �������� ������� � ������ ���������.
		i++;
		S.sort_simplex(f); //���������� ����� �� ����������� �������� �������
		Point Xh = S[S.Count() - 1]; //Xh - ����� � ���������� ��������� �������
		double Fh = f->Calculate(Xh);
		Point Xg = S[S.Count() - 2]; //Xg - ����� �� ��������� �� �������� ��������� �������
		double Fg = f->Calculate(Xg);
		Point Xl = S[0]; //Xl - ����� � ���������� ��������� �������
		double Fl = f->Calculate(Xl);
		
		Point X0 = S.centroid(S.Count() - 1); //���������� "������ �������" ���� ����� �� ����������� Xh

		Point Xr = (1 + reflection) * X0 - reflection * Xh; // ��������� ����� Xh ������������ Xc � ������������ reflection
		double Fr = f->Calculate(Xr);

		Point Xe, Xc;
		double Fe=0, Fc=0;

		bool Xe_exist = false;//��� ������
		bool Xh_changed = false;//��� ������
		bool Xc_exist = false;//��� ������

		//���� ����� Fr � ���� Fh, Fg, Fl
		if (Fr < Fl) { //������� ������� �����������, ������� ��������� ���
			Xe = (1 - expansion) * X0 + expansion * Xr; //���������� "����������"
			Fe = f->Calculate(Xe);
			Xe_exist = true;
			if (Fe < Fr)  S[S.Count() - 1] = Xe; //��������� �������� ����� �� ����� Xe: �������� Xh �������� Xe
			else S[S.Count() - 1] = Xr; //������������� ������� ������: �������� Xh �������� Xr
		}
		else if (Fr < Fg) S[S.Count() - 1] = Xr; //����� ����� Xr ��������: �������� Xh �������� Xr
		else {
			if (Fr < Fh) {
				S[S.Count() - 1] = Xr;
				Point t = Xh;
				Xh = Xr;
				Xr = t;
				double t1 = Fh;
				Fh = Fr;
				Fr = Fh;
				Xh_changed = true;
			}

			Xc = contraction * Xh + (1 - contraction) * X0; //���������� "c�����"
			Fc = f->Calculate(Xc);
			Xc_exist = true;
			if (Fc < Fh) S[S.Count() - 1] = Xc;
			else { //�������������� ����� ��������� ��������. ������ "���������� ������" ���������
				for (int j = 1; j < S.Count(); j++) {
					S[j] = Xl + shrink * (S[j] - Xl);
				}
			}
		}
		st_deviation = S.standard_deviation(f);
		
		//����� �� �����
		if(Xh_changed) printf(" % 3d | % 10.3f | %10.3f | % 10.3f | %10.3f | % 10.3f | %10.3f | % 10.3f | %10.3f |", i, Xl[0], Fl, Xg[0], Fg, Xr[0], Fr, Xh[0], Fh);
		else printf(" % 3d | %10.3f | %10.3f | % 10.3f | %10.3f | % 10.3f | %10.3f | % 10.3f | %10.3f |", i, Xl[0], Fl, Xg[0], Fg, Xh[0], Fh, Xr[0], Fr);
		if (Xe_exist) printf(" %10.3f | %10.3f |", Xe[0], Fe);
		else printf("     --     |     --     |");
		if (Xc_exist) printf(" %10.3f | %10.3f |", Xc[0], Fc);
		else printf("     --     |     --     |");
		printf(" %16.5f |\n", st_deviation);
		for (int j = 1; j < Xh.Dimensionality(); j++) {
			if (Xh_changed) printf("     | % 10.3f |            | % 10.3f |            | % 10.3f |            | % 10.3f |            |", Xl[j], Xg[j], Xr[j], Xh[j]);
			else printf("     | % 10.3f |            | % 10.3f |            | % 10.3f |            | % 10.3f |            |",Xl[j], Xg[j], Xh[j], Xr[j]);
			if (Xe_exist) printf(" %10.3f |            |", Xe[j]);
			else printf("            |            |");
			if (Xc_exist) printf(" %10.3f |            |", Xc[j]);
			else printf("            |            |");
			printf("                  |\n");
		}
		printf("-----|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------|------------------|\n");
	}
	Point Min = S[0]; //���������� ����� �� ������������� ��������� � ���������� ���������
	for (int i = 1; i < S.Count(); i++) {
		if (f->Calculate(Min) > f->Calculate(S[i])) Min = S[i];
	}
	printf("Result: %f\nPoint:\n",f->Calculate(Min));
	for (int i = 0; i < Min.Dimensionality(); i++) {
		printf(" X%d = %f\n", i + 1, Min[i]);
	}
	return Min;
}
