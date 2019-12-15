#include "COpponentModeling.h"

#include<Windows.h>
#include <iostream>
#include <fstream>

#include "CSymbols.h"

void COpponentModeling::CreateDir(std::string dirname)
{
	CreateDirectory(dirname.c_str(), NULL);
}

void COpponentModeling::PrwLogHandlist(int handnumber, int userchair, int betround, int log_param)
{
	if (handnumber > 0)
	{
		int my_graphpoints[11][15][15];

		//----------------------------------------------------------------------------------------------------------------------------
		// CREATING LOG DIR
		//---------------------------------------------------------------------------------------------------------------------------- 
		char my_dir[256];

		sprintf_s(my_dir, "C:/prwlog");
		CreateDir(my_dir);
		sprintf_s(my_dir, "C:/prwlog/%d", handnumber);
		CreateDir(my_dir);
		sprintf_s(my_dir, "C:/prwlog/%d/gnuscript", handnumber);
		CreateDir(my_dir);
		sprintf_s(my_dir, "C:/prwlog/%d", handnumber);
		//----------------------------------------------------------------------------------------------------------------------------
		// CREATING LOG FILES -> BLACK MAGIC :)
		//----------------------------------------------------------------------------------------------------------------------------
		char prw_list_buffer[256];
		char gnuscripdump_buffer[256];
		char gnuplot_buffer[256];
		char gnuscript_buffer[256];

		for (int f = 0;f<11;f++)
		{
			for (int i = 0;i<10;i++)
			{
				if (is_playing(i, static_cast<int>(g_symbols->get_playersplayingbits())) && i != g_symbols->get_userchair())
				{
					std::ofstream prw_list_obj;
					std::ofstream gnuplot_obj;
					std::ofstream gnuscript_obj;

					sprintf_s(prw_list_buffer, "%s/prw-handlog-%d-%d-%d-suitlog-%d", my_dir, i, betround, log_param, f);
					sprintf_s(gnuscripdump_buffer, "/prw-handlog-%d-%d-%d-suitlog-%d", i, betround, log_param, f);
					sprintf_s(gnuplot_buffer, "%s/gnuplot-handlog-%d-%d-%d-suitlog-%d", my_dir, i, betround, log_param, f);
					sprintf_s(gnuscript_buffer, "%s/gnuscript/gnuscript-%d", my_dir, log_param);

					gnuscript_obj.open(gnuscript_buffer, std::ios::app);

					gnuscript_obj << "set term png" << std::endl;
					gnuscript_obj << "set output '" << my_dir << "/gnuscript/suitlog_chair" << i << "_round" << betround << "_logparam" << log_param << "_suitlog_" << f << ".jpg'" << std::endl;
					gnuscript_obj << "load '" << my_dir << "/gnuplot-handlog-" << i << "-" << betround << "-" << log_param << "-suitlog-" << f << "'" << std::endl;

					gnuscript_obj.close();

					gnuplot_obj.open(gnuplot_buffer);

					gnuplot_obj << "set title 'Handrange ( chair: " << i << ", betround: " << betround << ", log: " << log_param << " )'" << std::endl;

					if (f == 0)
					{
						gnuplot_obj << "set xtics ('A' 0, 'K' 1, 'Q' 2, 'J' 3, 'T' 4, '9' 5, '8' 6, '7' 7, '6' 8, '5' 9, '4' 10, '3' 11, '2' 12)" << std::endl;
						gnuplot_obj << "set ytics ('A' 12, 'K' 11, 'Q' 10, 'J' 9, 'T' 8, '9' 7, '8' 6, '7' 5, '6' 4, '5' 3, '4' 2, '3' 1, '2' 0)" << std::endl;
					}
					if (f == 1)
					{
						gnuplot_obj << "set xtics ('Ah' 0, 'Kh' 1, 'Qh' 2, 'Jh' 3, 'Th' 4, '9h' 5, '8h' 6, '7h' 7, '6h' 8, '5h' 9, '4h' 10, '3h' 11, '2h' 12)" << std::endl;
						gnuplot_obj << "set ytics ('Ah' 12, 'Kh' 11, 'Qh' 10, 'Jh' 9, 'Th' 8, '9h' 7, '8h' 6, '7h' 5, '6h' 4, '5h' 3, '4h' 2, '3h' 1, '2h' 0)" << std::endl;
					}
					if (f == 2)
					{
						gnuplot_obj << "set xtics ('Ah' 0, 'Kh' 1, 'Qh' 2, 'Jh' 3, 'Th' 4, '9h' 5, '8h' 6, '7h' 7, '6h' 8, '5h' 9, '4h' 10, '3h' 11, '2h' 12)" << std::endl;
						gnuplot_obj << "set ytics ('Ad' 12, 'Kd' 11, 'Qd' 10, 'Jd' 9, 'Td' 8, '9d' 7, '8d' 6, '7d' 5, '6d' 4, '5d' 3, '4d' 2, '3d' 1, '2d' 0)" << std::endl;
					}
					if (f == 3)
					{
						gnuplot_obj << "set xtics ('Ah' 0, 'Kh' 1, 'Qh' 2, 'Jh' 3, 'Th' 4, '9h' 5, '8h' 6, '7h' 7, '6h' 8, '5h' 9, '4h' 10, '3h' 11, '2h' 12)" << std::endl;
						gnuplot_obj << "set ytics ('Ac' 12, 'Kc' 11, 'Qc' 10, 'Jc' 9, 'Tc' 8, '9c' 7, '8c' 6, '7c' 5, '6c' 4, '5c' 3, '4c' 2, '3c' 1, '2c' 0)" << std::endl;
					}
					if (f == 4)
					{
						gnuplot_obj << "set xtics ('Ah' 0, 'Kh' 1, 'Qh' 2, 'Jh' 3, 'Th' 4, '9h' 5, '8h' 6, '7h' 7, '6h' 8, '5h' 9, '4h' 10, '3h' 11, '2h' 12)" << std::endl;
						gnuplot_obj << "set ytics ('As' 12, 'Ks' 11, 'Qs' 10, 'Js' 9, 'Ts' 8, '9s' 7, '8s' 6, '7s' 5, '6s' 4, '5s' 3, '4s' 2, '3s' 1, '2s' 0)" << std::endl;
					}
					if (f == 5)
					{
						gnuplot_obj << "set xtics ('Ad' 0, 'Kd' 1, 'Qd' 2, 'Jd' 3, 'Td' 4, '9d' 5, '8d' 6, '7d' 7, '6d' 8, '5d' 9, '4d' 10, '3d' 11, '2d' 12)" << std::endl;
						gnuplot_obj << "set ytics ('Ad' 12, 'Kd' 11, 'Qd' 10, 'Jd' 9, 'Td' 8, '9d' 7, '8d' 6, '7d' 5, '6d' 4, '5d' 3, '4d' 2, '3d' 1, '2d' 0)" << std::endl;
					}
					if (f == 6)
					{
						gnuplot_obj << "set xtics ('Ad' 0, 'Kd' 1, 'Qd' 2, 'Jd' 3, 'Td' 4, '9d' 5, '8d' 6, '7d' 7, '6d' 8, '5d' 9, '4d' 10, '3d' 11, '2d' 12)" << std::endl;
						gnuplot_obj << "set ytics ('Ac' 12, 'Kc' 11, 'Qc' 10, 'Jc' 9, 'Tc' 8, '9c' 7, '8c' 6, '7c' 5, '6c' 4, '5c' 3, '4c' 2, '3c' 1, '2c' 0)" << std::endl;
					}
					if (f == 7)
					{
						gnuplot_obj << "set xtics ('Ad' 0, 'Kd' 1, 'Qd' 2, 'Jd' 3, 'Td' 4, '9d' 5, '8d' 6, '7d' 7, '6d' 8, '5d' 9, '4d' 10, '3d' 11, '2d' 12)" << std::endl;
						gnuplot_obj << "set ytics ('As' 12, 'Ks' 11, 'Qs' 10, 'Js' 9, 'Ts' 8, '9s' 7, '8s' 6, '7s' 5, '6s' 4, '5s' 3, '4s' 2, '3s' 1, '2s' 0)" << std::endl;
					}
					if (f == 8)
					{
						gnuplot_obj << "set xtics ('Ac' 0, 'Kc' 1, 'Qc' 2, 'Jc' 3, 'Tc' 4, '9c' 5, '8c' 6, '7c' 7, '6c' 8, '5c' 9, '4c' 10, '3c' 11, '2c' 12)" << std::endl;
						gnuplot_obj << "set ytics ('Ac' 12, 'Kc' 11, 'Qc' 10, 'Jc' 9, 'Tc' 8, '9c' 7, '8c' 6, '7c' 5, '6c' 4, '5c' 3, '4c' 2, '3c' 1, '2c' 0)" << std::endl;
					}
					if (f == 9)
					{
						gnuplot_obj << "set xtics ('Ac' 0, 'Kc' 1, 'Qc' 2, 'Jc' 3, 'Tc' 4, '9c' 5, '8c' 6, '7c' 7, '6c' 8, '5c' 9, '4c' 10, '3c' 11, '2c' 12)" << std::endl;
						gnuplot_obj << "set ytics ('As' 12, 'Ks' 11, 'Qs' 10, 'Js' 9, 'Ts' 8, '9s' 7, '8s' 6, '7s' 5, '6s' 4, '5s' 3, '4s' 2, '3s' 1, '2s' 0)" << std::endl;
					}
					if (f == 10)
					{
						gnuplot_obj << "set xtics ('As' 0, 'Ks' 1, 'Qs' 2, 'Js' 3, 'Ts' 4, '9s' 5, '8s' 6, '7s' 7, '6s' 8, '5s' 9, '4s' 10, '3s' 11, '2s' 12)" << std::endl;
						gnuplot_obj << "set ytics ('As' 12, 'Ks' 11, 'Qs' 10, 'Js' 9, 'Ts' 8, '9s' 7, '8s' 6, '7s' 5, '6s' 4, '5s' 3, '4s' 2, '3s' 1, '2s' 0)" << std::endl;
					}

					gnuplot_obj << "set xrange [-1:13]" << std::endl;
					gnuplot_obj << "set yrange [-1:13]" << std::endl;
					gnuplot_obj << "set dgrid3d 500,500,1" << std::endl;
					gnuplot_obj << "set view 0,270" << std::endl;
					gnuplot_obj << "set nosurface" << std::endl;
					gnuplot_obj << "set pm3d at b" << std::endl;

					gnuplot_obj << "splot '" << my_dir << gnuscripdump_buffer << "'" << std::endl;

					gnuplot_obj.close();

					for (int k = 0;k<15;k++)
						for (int j = 0;j<15;j++)
							my_graphpoints[f][j][k] = 0;

					for (int z = 0;z < _prw1326->chair[i].limit; z++)
					{
						int rank1 = _prw1326->chair[i].ranklo[z] % 13;
						int suit1 = _prw1326->chair[i].ranklo[z] - _prw1326->chair[i].ranklo[z] % 13;
						int rank2 = _prw1326->chair[i].rankhi[z] % 13;
						int suit2 = _prw1326->chair[i].rankhi[z] - _prw1326->chair[i].rankhi[z] % 13;

						if (f == 0)
						{
							if (rank1 > rank2)
							{
								if (suit1 == suit2)
									my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
								else
									my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
							}
							else
							{
								if (rank1 == rank2)
									my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
								else if (suit1 == suit2)
									my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
								else
									my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
							}
						}
						if (f == 1)
						{
							//hh
							if (suit1 == 0 && suit2 == 0)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 2)
						{
							//hd
							if (suit1 == 0 && suit2 == 13)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
							if (suit1 == 13 && suit2 == 0)
								my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 3)
						{
							//hc
							if (suit1 == 0 && suit2 == 26)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
							if (suit1 == 26 && suit2 == 0)
								my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 4)
						{
							//hs
							if (suit1 == 0 && suit2 == 39)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
							if (suit1 == 39 && suit2 == 0)
								my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 5)
						{
							//dd
							if (suit1 == 13 && suit2 == 13)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 6)
						{
							//dc
							if (suit1 == 13 && suit2 == 26)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
							if (suit1 == 26 && suit2 == 13)
								my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 7)
						{
							//ds
							if (suit1 == 13 && suit2 == 39)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
							if (suit1 == 39 && suit2 == 13)
								my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 8)
						{
							//cc
							if (suit1 == 26 && suit2 == 26)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 9)
						{
							//cs
							if (suit1 == 26 && suit2 == 39)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
							if (suit1 == 39 && suit2 == 26)
								my_graphpoints[f][12 - rank2 + 1][rank1 + 1] += _prw1326->chair[i].weight[z];
						}
						if (f == 10)
						{
							//ss
							if (suit1 == 39 && suit2 == 39)
								my_graphpoints[f][12 - rank1 + 1][rank2 + 1] += _prw1326->chair[i].weight[z];
						}
					}

					prw_list_obj.open(prw_list_buffer);

					for (int p = 0;p<15;p++)
					{
						for (int j = 0;j<15;j++)
						{
							if (p != 0 && j != 0)
								prw_list_obj << j - 1 << " " << p - 1 << " " << my_graphpoints[f][j][p] << std::endl;
							if (p == 0)
								prw_list_obj << j - 1 << " " << "-1" << " " << my_graphpoints[f][j][p] << std::endl;
							if (j == 0)
								prw_list_obj << "-1" << " " << p - 1 << " " << my_graphpoints[f][j][p] << std::endl;
						}
					}

					prw_list_obj.close();
				}
			}
		}
	}
}