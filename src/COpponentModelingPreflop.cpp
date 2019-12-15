#include "COpponentModeling.h"

#include <conio.h>

#include "CLogging.h"
#include "CSymbols.h"

void COpponentModeling::init(int listnum, int weight)
{
	_prw1326->chair[listnum].limit = 0;
	int counter = 0;

	//1. AA
	Prw1326AddPocketPair(listnum, 12, weight);
	//2. KK
	Prw1326AddPocketPair(listnum, 11, weight);
	//3. AKs
	Prw1326AddSuit(listnum, 12, 11, weight);
	//4. QQ
	Prw1326AddPocketPair(listnum, 10, weight);
	//5. AKo
	Prw1326AddOffSuit(listnum, 12, 11, weight);
	//6. JJ
	Prw1326AddPocketPair(listnum, 9, weight);
	//7. AQs
	Prw1326AddSuit(listnum, 12, 10, weight);
	//8. TT
	Prw1326AddPocketPair(listnum, 8, weight);
	//9. AQo
	Prw1326AddOffSuit(listnum, 12, 10, weight);
	//10. 99
	Prw1326AddPocketPair(listnum, 7, weight);

	//11. AJs
	Prw1326AddSuit(listnum, 12, 9, weight);
	//12. 88
	Prw1326AddPocketPair(listnum, 6, weight);
	//13. ATs
	Prw1326AddSuit(listnum, 12, 8, weight);
	//14. AJo
	Prw1326AddOffSuit(listnum, 12, 9, weight);
	//15. 77
	Prw1326AddPocketPair(listnum, 5, weight);
	//16. 66
	Prw1326AddPocketPair(listnum, 4, weight);
	//17. ATo
	Prw1326AddOffSuit(listnum, 12, 8, weight);
	//18. A9s
	Prw1326AddSuit(listnum, 12, 7, weight);
	//19. 55
	Prw1326AddPocketPair(listnum, 3, weight);
	//20. A8s
	Prw1326AddSuit(listnum, 12, 6, weight);

	//21. KQs
	Prw1326AddSuit(listnum, 11, 10, weight);
	//22. 44
	Prw1326AddPocketPair(listnum, 2, weight);
	//23. A9o
	Prw1326AddOffSuit(listnum, 12, 7, weight);
	//24. A7s
	Prw1326AddSuit(listnum, 12, 5, weight);
	//25. KJs
	Prw1326AddSuit(listnum, 11, 9, weight);
	//26. A5s
	Prw1326AddSuit(listnum, 12, 3, weight);
	//27. A8o
	Prw1326AddOffSuit(listnum, 12, 6, weight);
	//28. A6s
	Prw1326AddSuit(listnum, 12, 4, weight);
	//29. A4s
	Prw1326AddSuit(listnum, 12, 2, weight);
	//30. 33
	Prw1326AddPocketPair(listnum, 1, weight);

	//31. KTs
	Prw1326AddSuit(listnum, 11, 8, weight);
	//32. A7o
	Prw1326AddOffSuit(listnum, 12, 5, weight);
	//33. A3s
	Prw1326AddSuit(listnum, 12, 1, weight);
	//34. KQo
	Prw1326AddOffSuit(listnum, 11, 10, weight);
	//35. A2s
	Prw1326AddSuit(listnum, 12, 0, weight);
	//36. A5o
	Prw1326AddOffSuit(listnum, 12, 3, weight);
	//37. A6o
	Prw1326AddOffSuit(listnum, 12, 4, weight);
	//38. A4o
	Prw1326AddOffSuit(listnum, 12, 2, weight);
	//39. KJo
	Prw1326AddOffSuit(listnum, 11, 9, weight);
	//40. QJs
	Prw1326AddSuit(listnum, 10, 9, weight);

	//41. A3o
	Prw1326AddOffSuit(listnum, 12, 1, weight);
	//42. 22
	Prw1326AddPocketPair(listnum, 0, weight);
	//43. K9s
	Prw1326AddSuit(listnum, 11, 7, weight);
	//44. A2o
	Prw1326AddOffSuit(listnum, 12, 0, weight);
	//45. KTo
	Prw1326AddOffSuit(listnum, 11, 8, weight);
	//46. QTs
	Prw1326AddSuit(listnum, 10, 8, weight);
	//47. K8s
	Prw1326AddSuit(listnum, 11, 6, weight);
	//48. K7s
	Prw1326AddSuit(listnum, 11, 5, weight);
	//49. JTs
	Prw1326AddSuit(listnum, 9, 8, weight);
	//50. K9o
	Prw1326AddOffSuit(listnum, 11, 7, weight);

	//51. K6s
	Prw1326AddSuit(listnum, 11, 4, weight);
	//52. QJo
	Prw1326AddOffSuit(listnum, 10, 9, weight);
	//53. Q9s
	Prw1326AddSuit(listnum, 10, 7, weight);
	//54. K5s
	Prw1326AddSuit(listnum, 11, 3, weight);
	//55. K8o
	Prw1326AddOffSuit(listnum, 11, 6, weight);
	//56. K4s
	Prw1326AddSuit(listnum, 11, 2, weight);
	//57. QTo
	Prw1326AddOffSuit(listnum, 10, 8, weight);
	//58. K7o
	Prw1326AddOffSuit(listnum, 11, 5, weight);
	//59. K3s
	Prw1326AddSuit(listnum, 11, 1, weight);
	//60. K2s
	Prw1326AddSuit(listnum, 11, 0, weight);

	//61. Q8s
	Prw1326AddSuit(listnum, 10, 6, weight);
	//62. K6o
	Prw1326AddOffSuit(listnum, 11, 4, weight);
	//63. J9s
	Prw1326AddSuit(listnum, 9, 7, weight);
	//64. K5o
	Prw1326AddOffSuit(listnum, 11, 3, weight);
	//65. Q9o
	Prw1326AddOffSuit(listnum, 10, 7, weight);
	//66. JTo
	Prw1326AddOffSuit(listnum, 9, 8, weight);
	//67. K4o
	Prw1326AddOffSuit(listnum, 11, 2, weight);
	//68. Q7s
	Prw1326AddSuit(listnum, 10, 5, weight);
	//69. T9s
	Prw1326AddSuit(listnum, 8, 7, weight);
	//70. Q6s
	Prw1326AddSuit(listnum, 10, 4, weight);

	//71. K3o
	Prw1326AddOffSuit(listnum, 11, 1, weight);
	//72. J8s
	Prw1326AddSuit(listnum, 9, 6, weight);
	//73. Q5s
	Prw1326AddSuit(listnum, 10, 3, weight);
	//74. K2o
	Prw1326AddOffSuit(listnum, 11, 0, weight);
	//75. Q8o
	Prw1326AddOffSuit(listnum, 10, 6, weight);
	//76. Q4s
	Prw1326AddSuit(listnum, 10, 2, weight);
	//77. J9o
	Prw1326AddOffSuit(listnum, 9, 7, weight);
	//78. Q3s
	Prw1326AddSuit(listnum, 10, 1, weight);
	//79. T8s
	Prw1326AddSuit(listnum, 8, 6, weight);
	//80. J7s
	Prw1326AddSuit(listnum, 9, 5, weight);

	//81. Q7o
	Prw1326AddOffSuit(listnum, 10, 5, weight);
	//82. Q2s
	Prw1326AddSuit(listnum, 10, 0, weight);
	//83. Q6o
	Prw1326AddOffSuit(listnum, 10, 4, weight);
	//84. 98s
	Prw1326AddSuit(listnum, 7, 6, weight);
	//85. Q5o
	Prw1326AddOffSuit(listnum, 10, 3, weight);
	//86. J8o
	Prw1326AddOffSuit(listnum, 9, 6, weight);
	//87. T9o
	Prw1326AddOffSuit(listnum, 8, 7, weight);
	//88. J6s
	Prw1326AddSuit(listnum, 9, 4, weight);
	//89. T7s
	Prw1326AddSuit(listnum, 8, 5, weight);
	//90. J5s
	Prw1326AddSuit(listnum, 9, 3, weight);

	//91. Q4o
	Prw1326AddOffSuit(listnum, 10, 2, weight);
	//92. J4s
	Prw1326AddSuit(listnum, 9, 2, weight);
	//93. J7o
	Prw1326AddOffSuit(listnum, 9, 5, weight);
	//94. Q3o
	Prw1326AddOffSuit(listnum, 10, 1, weight);
	//95. 97s
	Prw1326AddSuit(listnum, 7, 5, weight);
	//96. T8o
	Prw1326AddOffSuit(listnum, 8, 6, weight);
	//97. J3s
	Prw1326AddSuit(listnum, 9, 1, weight);
	//98. T6s
	Prw1326AddSuit(listnum, 8, 4, weight);
	//99. Q2o
	Prw1326AddOffSuit(listnum, 10, 0, weight);
	//100. J2s
	Prw1326AddSuit(listnum, 9, 0, weight);

	//101. 87s
	Prw1326AddSuit(listnum, 6, 5, weight);
	//102. J6o
	Prw1326AddOffSuit(listnum, 9, 4, weight);
	//103. 98o
	Prw1326AddOffSuit(listnum, 7, 6, weight);
	//104. T7o
	Prw1326AddOffSuit(listnum, 8, 5, weight);
	//105. 96s
	Prw1326AddSuit(listnum, 7, 4, weight);
	//106. J5o
	Prw1326AddOffSuit(listnum, 9, 3, weight);
	//107. T5s
	Prw1326AddSuit(listnum, 8, 3, weight);
	//108. T4s
	Prw1326AddSuit(listnum, 8, 2, weight);
	//109. 86s
	Prw1326AddSuit(listnum, 6, 4, weight);
	//110. J4o
	Prw1326AddOffSuit(listnum, 9, 2, weight);

	//111. T6o
	Prw1326AddOffSuit(listnum, 8, 4, weight);
	//112. 97o
	Prw1326AddOffSuit(listnum, 7, 5, weight);
	//113. T3s
	Prw1326AddSuit(listnum, 8, 1, weight);
	//114. 76s
	Prw1326AddSuit(listnum, 5, 4, weight);
	//115. 95s
	Prw1326AddSuit(listnum, 7, 3, weight);
	//116. J3o
	Prw1326AddOffSuit(listnum, 9, 1, weight);
	//117. T2s
	Prw1326AddSuit(listnum, 8, 0, weight);
	//118. 87o
	Prw1326AddOffSuit(listnum, 6, 5, weight);
	//119. 85s
	Prw1326AddSuit(listnum, 6, 3, weight);
	//120. 96o
	Prw1326AddOffSuit(listnum, 7, 4, weight);

	//121. T5o
	Prw1326AddOffSuit(listnum, 8, 3, weight);
	//122. J2o
	Prw1326AddOffSuit(listnum, 9, 0, weight);
	//123. 75s
	Prw1326AddSuit(listnum, 5, 3, weight);
	//124. 94s
	Prw1326AddSuit(listnum, 7, 2, weight);
	//125. T4o
	Prw1326AddOffSuit(listnum, 8, 2, weight);
	//126. 65s
	Prw1326AddSuit(listnum, 4, 3, weight);
	//127. 86o
	Prw1326AddOffSuit(listnum, 6, 4, weight);
	//128. 93s
	Prw1326AddSuit(listnum, 7, 1, weight);
	//129. 84s
	Prw1326AddSuit(listnum, 6, 2, weight);
	//130. 95o
	Prw1326AddOffSuit(listnum, 7, 3, weight);

	//131. T3o
	Prw1326AddOffSuit(listnum, 8, 1, weight);
	//132. 76o
	Prw1326AddOffSuit(listnum, 5, 4, weight);
	//133. 92s
	Prw1326AddSuit(listnum, 7, 0, weight);
	//134. 74s
	Prw1326AddSuit(listnum, 5, 2, weight);
	//135. 54s
	Prw1326AddSuit(listnum, 3, 2, weight);
	//136. T2o
	Prw1326AddOffSuit(listnum, 8, 0, weight);
	//137. 85o
	Prw1326AddOffSuit(listnum, 6, 3, weight);
	//138. 64s
	Prw1326AddSuit(listnum, 4, 2, weight);
	//139. 83s
	Prw1326AddSuit(listnum, 6, 1, weight);
	//140. 94o
	Prw1326AddOffSuit(listnum, 7, 2, weight);

	//141. 75o
	Prw1326AddOffSuit(listnum, 5, 3, weight);
	//142. 82s
	Prw1326AddSuit(listnum, 6, 0, weight);
	//143. 73s
	Prw1326AddSuit(listnum, 5, 1, weight);
	//144. 93o
	Prw1326AddOffSuit(listnum, 7, 1, weight);
	//145. 65o
	Prw1326AddOffSuit(listnum, 4, 3, weight);
	//146. 53s
	Prw1326AddSuit(listnum, 3, 1, weight);
	//147. 63s
	Prw1326AddSuit(listnum, 4, 1, weight);
	//148. 84o
	Prw1326AddOffSuit(listnum, 6, 2, weight);
	//149. 92o
	Prw1326AddOffSuit(listnum, 7, 0, weight);
	//150. 43s
	Prw1326AddSuit(listnum, 2, 1, weight);

	//151. 74o
	Prw1326AddOffSuit(listnum, 5, 2, weight);
	//152. 72s
	Prw1326AddSuit(listnum, 5, 0, weight);
	//153. 54o
	Prw1326AddOffSuit(listnum, 3, 2, weight);
	//154. 64o
	Prw1326AddOffSuit(listnum, 4, 2, weight);
	//155. 52s
	Prw1326AddSuit(listnum, 3, 0, weight);
	//156. 62s
	Prw1326AddSuit(listnum, 4, 0, weight);
	//157. 83o
	Prw1326AddOffSuit(listnum, 6, 1, weight);
	//158. 42s
	Prw1326AddSuit(listnum, 2, 0, weight);
	//159. 82o
	Prw1326AddOffSuit(listnum, 6, 0, weight);
	//160. 73o
	Prw1326AddOffSuit(listnum, 5, 1, weight);

	//161. 53o
	Prw1326AddOffSuit(listnum, 3, 1, weight);
	//162. 63o
	Prw1326AddOffSuit(listnum, 4, 1, weight);
	//163. 32s
	Prw1326AddSuit(listnum, 1, 0, weight);
	//164. 43o
	Prw1326AddOffSuit(listnum, 2, 1, weight);
	//165. 72o
	Prw1326AddOffSuit(listnum, 5, 0, weight);
	//166. 52o
	Prw1326AddOffSuit(listnum, 3, 0, weight);
	//167. 62o
	Prw1326AddOffSuit(listnum, 4, 0, weight);
	//168. 42o
	Prw1326AddOffSuit(listnum, 2, 0, weight);
	//169. 32o
	Prw1326AddOffSuit(listnum, 1, 0, weight);
}

void COpponentModeling::PrwSetPreflopTopList(int listnum, double play_pct, int weight)
{
	int include = (int)floor(play_pct * 1326) + 1;

	g_log->WriteLog(eSeverityDebug, eCatOpponentModeling, "Raise: include -> %d\n", include);

	//1. AA
	Prw1326GetPocketPair(listnum, 12);
	//2. KK
	Prw1326GetPocketPair(listnum, 11);
	//3. AKs
	Prw1326GetSuit(listnum, 12, 11);
	//4. QQ
	Prw1326GetPocketPair(listnum, 10);
	//5. AKo
	Prw1326GetOffSuit(listnum, 12, 11);
	//6. JJ
	Prw1326GetPocketPair(listnum, 9);
	//7. AQs
	Prw1326GetSuit(listnum, 12, 10);
	//8. TT
	Prw1326GetPocketPair(listnum, 8);

	//9. AQo
	if (include > 50) { Prw1326GetOffSuit(listnum, 12, 10); }
	//10. 99
	if (include > 56) { Prw1326GetPocketPair(listnum, 7); }


	//11. AJs
	if (include > 60) { Prw1326GetSuit(listnum, 12, 9); }
	//12. 88
	if (include > 64) { Prw1326GetPocketPair(listnum, 6); }
	//13. ATs
	if (include > 70) { Prw1326GetSuit(listnum, 12, 8); }
	//14. AJo
	if (include > 74) { Prw1326GetOffSuit(listnum, 12, 9); }
	//15. 77
	if (include > 86) { Prw1326GetPocketPair(listnum, 5); }
	//16. 66
	if (include > 90) { Prw1326GetPocketPair(listnum, 4); }
	//17. ATo
	if (include > 94) { Prw1326GetOffSuit(listnum, 12, 8); }
	//18. A9s
	if (include > 98) { Prw1326GetSuit(listnum, 12, 7); }
	//19. 55
	if (include > 110) { Prw1326GetPocketPair(listnum, 3); }
	//20. A8s
	if (include > 122) { Prw1326GetSuit(listnum, 12, 6); }


	//21. KQs
	if (include > 126) { Prw1326GetSuit(listnum, 11, 10); }
	//22. 44
	if (include > 130) { Prw1326GetPocketPair(listnum, 2); }
	//23. A9o
	if (include > 136) { Prw1326GetOffSuit(listnum, 12, 7); }
	//24. A7s
	if (include > 148) { Prw1326GetSuit(listnum, 12, 5); }
	//25. KJs
	if (include > 152) { Prw1326GetSuit(listnum, 11, 9); }
	//26. A5s
	if (include > 164) { Prw1326GetSuit(listnum, 12, 3); }
	//27. A8o
	if (include > 168) { Prw1326GetOffSuit(listnum, 12, 6); }
	//28. A6s
	if (include > 172) { Prw1326GetSuit(listnum, 12, 4); }
	//29. A4s
	if (include > 184) { Prw1326GetSuit(listnum, 12, 2); }
	//30. 33
	if (include > 188) { Prw1326GetPocketPair(listnum, 1); }


	//31. KTs
	if (include > 200) { Prw1326GetSuit(listnum, 11, 8); }
	//32. A7o
	if (include > 204) { Prw1326GetOffSuit(listnum, 12, 5); }
	//33. A3s
	if (include > 208) { Prw1326GetSuit(listnum, 12, 1); }
	//34. KQo
	if (include > 214) { Prw1326GetOffSuit(listnum, 11, 10); }
	//35. A2s
	if (include > 218) { Prw1326GetSuit(listnum, 12, 0); }
	//36. A5o
	if (include > 230) { Prw1326GetOffSuit(listnum, 12, 3); }
	//37. A6o
	if (include > 234) { Prw1326GetOffSuit(listnum, 12, 4); }
	//38. A4o
	if (include > 246) { Prw1326GetOffSuit(listnum, 12, 2); }
	//39. KJo
	if (include > 250) { Prw1326GetOffSuit(listnum, 11, 9); }
	//40. QJs
	if (include > 254) { Prw1326GetSuit(listnum, 10, 9); }


	//41. A3o
	if (include > 258) { Prw1326GetOffSuit(listnum, 12, 1); }
	//42. 22
	if (include > 270) { Prw1326GetPocketPair(listnum, 0); }
	//43. K9s
	if (include > 274) { Prw1326GetSuit(listnum, 11, 7); }
	//44. A2o
	if (include > 286) { Prw1326GetOffSuit(listnum, 12, 0); }
	//45. KTo
	if (include > 290) { Prw1326GetOffSuit(listnum, 11, 8); }
	//46. QTs
	if (include > 294) { Prw1326GetSuit(listnum, 10, 8); }
	//47. K8s
	if (include > 306) { Prw1326GetSuit(listnum, 11, 6); }
	//48. K7s
	if (include > 310) { Prw1326GetSuit(listnum, 11, 5); }
	//49. JTs
	if (include > 310) { Prw1326GetSuit(listnum, 9, 8); }
	//50. K9o
	if (include > 314) { Prw1326GetOffSuit(listnum, 11, 7); }


	//51. K6s
	if (include > 318) { Prw1326GetSuit(listnum, 11, 4); }
	//52. QJo
	if (include > 330) { Prw1326GetOffSuit(listnum, 10, 9); }
	//53. Q9s
	if (include > 336) { Prw1326GetSuit(listnum, 10, 7); }
	//54. K5s
	if (include > 348) { Prw1326GetSuit(listnum, 11, 3); }
	//55. K8o
	if (include > 352) { Prw1326GetOffSuit(listnum, 11, 6); }
	//56. K4s
	if (include > 356) { Prw1326GetSuit(listnum, 11, 2); }
	//57. QTo
	if (include > 360) { Prw1326GetOffSuit(listnum, 10, 8); }
	//58. K7o
	if (include > 372) { Prw1326GetOffSuit(listnum, 11, 5); }
	//59. K3s
	if (include > 384) { Prw1326GetSuit(listnum, 11, 1); }
	//60. K2s
	if (include > 396) { Prw1326GetSuit(listnum, 11, 0); }


	//61. Q8s
	if (include > 408) { Prw1326GetSuit(listnum, 10, 6); }
	//62. K6o
	if (include > 412) { Prw1326GetOffSuit(listnum, 11, 4); }
	//63. J9s
	if (include > 424) { Prw1326GetSuit(listnum, 9, 7); }
	//64. K5o
	if (include > 428) { Prw1326GetOffSuit(listnum, 11, 3); }
	//65. Q9o
	if (include > 432) { Prw1326GetOffSuit(listnum, 10, 7); }
	//66. JTo
	if (include > 436) { Prw1326GetOffSuit(listnum, 9, 8); }
	//67. K4o
	if (include > 448) { Prw1326GetOffSuit(listnum, 11, 2); }
	//68. Q7s
	if (include > 452) { Prw1326GetSuit(listnum, 10, 5); }
	//69. T9s
	if (include > 456) { Prw1326GetSuit(listnum, 8, 7); }
	//70. Q6s
	if (include > 460) { Prw1326GetSuit(listnum, 10, 4); }


	//71. K3o
	if (include > 464) { Prw1326GetOffSuit(listnum, 11, 1); }
	//72. J8s
	if (include > 476) { Prw1326GetSuit(listnum, 9, 6); }
	//73. Q5s
	if (include > 482) { Prw1326GetSuit(listnum, 10, 3); }
	//74. K2o
	if (include > 494) { Prw1326GetOffSuit(listnum, 11, 0); }
	//75. Q8o
	if (include > 506) { Prw1326GetOffSuit(listnum, 10, 6); }
	//76. Q4s
	if (include > 510) { Prw1326GetSuit(listnum, 10, 2); }
	//77. J9o
	if (include > 522) { Prw1326GetOffSuit(listnum, 9, 7); }
	//78. Q3s
	if (include > 526) { Prw1326GetSuit(listnum, 10, 1); }
	//79. T8s
	if (include > 538) { Prw1326GetSuit(listnum, 8, 6); }
	//80. J7s
	if (include > 542) { Prw1326GetSuit(listnum, 9, 5); }


	//81. Q7o
	if (include > 554) { Prw1326GetOffSuit(listnum, 10, 5); }
	//82. Q2s
	if (include > 566) { Prw1326GetSuit(listnum, 10, 0); }
	//83. Q6o
	if (include > 570) { Prw1326GetOffSuit(listnum, 10, 4); }
	//84. 98s
	if (include > 582) { Prw1326GetSuit(listnum, 7, 6); }
	//85. Q5o
	if (include > 586) { Prw1326GetOffSuit(listnum, 10, 3); }
	//86. J8o
	if (include > 590) { Prw1326GetOffSuit(listnum, 9, 6); }
	//87. T9o
	if (include > 594) { Prw1326GetOffSuit(listnum, 8, 7); }
	//88. J6s
	if (include > 598) { Prw1326GetSuit(listnum, 9, 4); }
	//89. T7s
	if (include > 602) { Prw1326GetSuit(listnum, 8, 5); }
	//90. J5s
	if (include > 614) { Prw1326GetSuit(listnum, 9, 3); }


	//91. Q4o
	if (include > 626) { Prw1326GetOffSuit(listnum, 10, 2); }
	//92. J4s
	if (include > 630) { Prw1326GetSuit(listnum, 9, 2); }
	//93. J7o
	if (include > 634) { Prw1326GetOffSuit(listnum, 9, 5); }
	//94. Q3o
	if (include > 640) { Prw1326GetOffSuit(listnum, 10, 1); }
	//95. 97s
	if (include > 644) { Prw1326GetSuit(listnum, 7, 5); }
	//96. T8o
	if (include > 656) { Prw1326GetOffSuit(listnum, 8, 6); }
	//97. J3s
	if (include > 668) { Prw1326GetSuit(listnum, 9, 1); }
	//98. T6s
	if (include > 680) { Prw1326GetSuit(listnum, 8, 4); }
	//99. Q2o
	if (include > 684) { Prw1326GetOffSuit(listnum, 10, 0); }
	//100. J2s
	if (include > 688) { Prw1326GetSuit(listnum, 9, 0); }


	//101. 87s
	if (include > 700) { Prw1326GetSuit(listnum, 6, 5); }
	//102. J6o
	if (include > 704) { Prw1326GetOffSuit(listnum, 9, 4); }
	//103. 98o
	if (include > 708) { Prw1326GetOffSuit(listnum, 7, 6); }
	//104. T7o
	if (include > 720) { Prw1326GetOffSuit(listnum, 8, 5); }
	//105. 96s
	if (include > 724) { Prw1326GetSuit(listnum, 7, 4); }
	//106. J5o
	if (include > 736) { Prw1326GetOffSuit(listnum, 9, 3); }
	//107. T5s
	if (include > 740) { Prw1326GetSuit(listnum, 8, 3); }
	//108. T4s
	if (include > 752) { Prw1326GetSuit(listnum, 8, 2); }
	//109. 86s
	if (include > 756) { Prw1326GetSuit(listnum, 6, 4); }
	//110. J4o
	if (include > 760) { Prw1326GetOffSuit(listnum, 9, 2); }


	//111. T6o
	if (include > 772) { Prw1326GetOffSuit(listnum, 8, 4); }
	//112. 97o
	if (include > 776) { Prw1326GetOffSuit(listnum, 7, 5); }
	//113. T3s
	if (include > 780) { Prw1326GetSuit(listnum, 8, 1); }
	//114. 76s
	if (include > 786) { Prw1326GetSuit(listnum, 5, 4); }
	//115. 95s
	if (include > 798) { Prw1326GetSuit(listnum, 7, 3); }
	//116. J3o
	if (include > 802) { Prw1326GetOffSuit(listnum, 9, 1); }
	//117. T2s
	if (include > 814) { Prw1326GetSuit(listnum, 8, 0); }
	//118. 87o
	if (include > 818) { Prw1326GetOffSuit(listnum, 6, 5); }
	//119. 85s
	if (include > 830) { Prw1326GetSuit(listnum, 6, 3); }
	//120. 96o
	if (include > 842) { Prw1326GetOffSuit(listnum, 7, 4); }


	//121. T5o
	if (include > 846) { Prw1326GetOffSuit(listnum, 8, 3); }
	//122. J2o
	if (include > 850) { Prw1326GetOffSuit(listnum, 9, 0); }
	//123. 75s
	if (include > 862) { Prw1326GetSuit(listnum, 5, 3); }
	//124. 94s
	if (include > 874) { Prw1326GetSuit(listnum, 7, 2); }
	//125. T4o
	if (include > 886) { Prw1326GetOffSuit(listnum, 8, 2); }
	//126. 65s
	if (include > 890) { Prw1326GetSuit(listnum, 4, 3); }
	//127. 86o
	if (include > 894) { Prw1326GetOffSuit(listnum, 6, 4); }
	//128. 93s
	if (include > 906) { Prw1326GetSuit(listnum, 7, 1); }
	//129. 84s
	if (include > 918) { Prw1326GetSuit(listnum, 6, 2); }
	//130. 95o
	if (include > 922) { Prw1326GetOffSuit(listnum, 7, 3); }


	//131. T3o
	if (include > 922) { Prw1326GetOffSuit(listnum, 8, 1); }
	//132. 76o
	if (include > 926) { Prw1326GetOffSuit(listnum, 5, 4); }
	//133. 92s
	if (include > 930) { Prw1326GetSuit(listnum, 7, 0); }
	//134. 74s
	if (include > 942) { Prw1326GetSuit(listnum, 5, 2); }
	//135. 54s
	if (include > 954) { Prw1326GetSuit(listnum, 3, 2); }
	//136. T2o
	if (include > 966) { Prw1326GetOffSuit(listnum, 8, 0); }
	//137. 85o
	if (include > 970) { Prw1326GetOffSuit(listnum, 6, 3); }
	//138. 64s
	if (include > 982) { Prw1326GetSuit(listnum, 4, 2); }
	//139. 85o
	if (include > 986) { Prw1326GetSuit(listnum, 6, 1); }
	//140. 94o
	if (include > 998) { Prw1326GetOffSuit(listnum, 7, 2); }


	//141. 75o
	if (include > 1002) { Prw1326GetOffSuit(listnum, 5, 3); }
	//142. 82s
	if (include > 1014) { Prw1326GetSuit(listnum, 6, 0); }
	//143. 73s
	if (include > 1026) { Prw1326GetSuit(listnum, 5, 1); }
	//144. 93o
	if (include > 1038) { Prw1326GetOffSuit(listnum, 7, 1); }
	//145. 65o
	if (include > 1042) { Prw1326GetOffSuit(listnum, 4, 3); }
	//146. 53s
	if (include > 1054) { Prw1326GetSuit(listnum, 3, 1); }
	//147. 63s
	if (include > 1058) { Prw1326GetSuit(listnum, 4, 1); }
	//148. 84o
	if (include > 1070) { Prw1326GetOffSuit(listnum, 6, 2); }
	//149. 92o
	if (include > 1082) { Prw1326GetOffSuit(listnum, 7, 0); }
	//150. 43s
	if (include > 1086) { Prw1326GetSuit(listnum, 2, 1); }


	//151. 74o
	if (include > 1098) { Prw1326GetOffSuit(listnum, 5, 2); }
	//152. 72s
	if (include > 1110) { Prw1326GetSuit(listnum, 5, 0); }
	//153. 54o
	if (include > 1114) { Prw1326GetOffSuit(listnum, 3, 2); }
	//154. 64o
	if (include > 1126) { Prw1326GetOffSuit(listnum, 4, 2); }
	//155. 52s
	if (include > 1138) { Prw1326GetSuit(listnum, 3, 0); }
	//156. 62s
	if (include > 1150) { Prw1326GetSuit(listnum, 4, 0); }
	//157. 83o
	if (include > 1162) { Prw1326GetOffSuit(listnum, 6, 1); }
	//158. 42s
	if (include > 1174) { Prw1326GetSuit(listnum, 2, 0); }
	//159. 82o
	if (include > 1186) { Prw1326GetOffSuit(listnum, 6, 0); }
	//160. 73o
	if (include > 1198) { Prw1326GetOffSuit(listnum, 5, 1); }


	//161. 53o
	if (include > 1210) { Prw1326GetOffSuit(listnum, 3, 1); }
	//162. 63o
	if (include > 1222) { Prw1326GetOffSuit(listnum, 4, 1); }
	//163. 32s
	if (include > 1234) { Prw1326GetSuit(listnum, 1, 0); }
	//164. 43o
	if (include > 1246) { Prw1326GetOffSuit(listnum, 2, 1); }
	//165. 72o
	if (include > 1258) { Prw1326GetOffSuit(listnum, 5, 0); }
	//166. 52o
	if (include > 1270) { Prw1326GetOffSuit(listnum, 3, 0); }
	//167. 62o
	if (include > 1282) { Prw1326GetOffSuit(listnum, 4, 0); }
	//168. 42o
	if (include > 1294) { Prw1326GetOffSuit(listnum, 2, 0); }
	//169. 32o
	if (include > 1306) { Prw1326GetOffSuit(listnum, 1, 0); }

}

void COpponentModeling::PrwSetPreflopMiddleList(int listnum, double play_pct, double exclude_pct, int weight)
{
	int include = (int)floor(play_pct * 1326) + 1;
	int exclude = (int)floor(exclude_pct * 1326);

	g_log->WriteLog(eSeverityDebug, eCatOpponentModeling, "Call: include -> %d exclude -> %d\n", include, exclude);

	//1. AA
	if (exclude == 0) { Prw1326GetPocketPair(listnum, 12); }
	//2. KK
	if (7 > exclude) { Prw1326GetPocketPair(listnum, 11); }
	//3. AKs
	if (13 > exclude) { Prw1326GetSuit(listnum, 12, 11); }
	//4. QQ
	if (19 > exclude) { Prw1326GetPocketPair(listnum, 10); }
	//5. AKo
	if (25 > exclude) { Prw1326GetOffSuit(listnum, 12, 11); }
	//6. JJ
	if (31 > exclude) { Prw1326GetPocketPair(listnum, 9); }
	//7. AQs
	if (35 > exclude) { Prw1326GetSuit(listnum, 12, 10); }
	//8. TT
	if (39 > exclude) { Prw1326GetPocketPair(listnum, 8); }
	//9. AQo
	if (include > 50 && 51 > exclude) { Prw1326GetOffSuit(listnum, 12, 10); }
	//10. 99
	if (include > 56 && 57 > exclude) { Prw1326GetPocketPair(listnum, 7); }


	//11. AJs
	if (include > 60 && 61 > exclude) { Prw1326GetSuit(listnum, 12, 9); }
	//12. 88
	if (include > 64 && 65 > exclude) { Prw1326GetPocketPair(listnum, 6); }
	//13. ATs
	if (include > 70 && 71 > exclude) { Prw1326GetSuit(listnum, 12, 8); }
	//14. AJo
	if (include > 74 && 75 > exclude) { Prw1326GetOffSuit(listnum, 12, 9); }
	//15. 77
	if (include > 86 && 87 > exclude) { Prw1326GetPocketPair(listnum, 5); }
	//16. 66
	if (include > 90 && 91 > exclude) { Prw1326GetPocketPair(listnum, 4); }
	//17. ATo
	if (include > 94 && 95 > exclude) { Prw1326GetOffSuit(listnum, 12, 8); }
	//18. A9s
	if (include > 98 && 99 > exclude) { Prw1326GetSuit(listnum, 12, 7); }
	//19. 55
	if (include > 110 && 111 > exclude) { Prw1326GetPocketPair(listnum, 3); }
	//20. A8s
	if (include > 122 && 123 > exclude) { Prw1326GetSuit(listnum, 12, 6); }


	//21. KQs
	if (include > 126 && 127 > exclude) { Prw1326GetSuit(listnum, 11, 10); }
	//22. 44
	if (include > 130 && 131 > exclude) { Prw1326GetPocketPair(listnum, 2); }
	//23. A9o
	if (include > 136 && 137 > exclude) { Prw1326GetOffSuit(listnum, 12, 7); }
	//24. A7s
	if (include > 148 && 149 > exclude) { Prw1326GetSuit(listnum, 12, 5); }
	//25. KJs
	if (include > 152 && 153 > exclude) { Prw1326GetSuit(listnum, 11, 9); }
	//26. A5s
	if (include > 164 && 165 > exclude) { Prw1326GetSuit(listnum, 12, 3); }
	//27. A8o
	if (include > 168 && 169 > exclude) { Prw1326GetOffSuit(listnum, 12, 6); }
	//28. A6s
	if (include > 172 && 173 > exclude) { Prw1326GetSuit(listnum, 12, 4); }
	//29. A4s
	if (include > 184 && 185 > exclude) { Prw1326GetSuit(listnum, 12, 2); }
	//30. 33
	if (include > 188 && 189 > exclude) { Prw1326GetPocketPair(listnum, 1); }


	//31. KTs
	if (include > 200 && 201 > exclude) { Prw1326GetSuit(listnum, 11, 8); }
	//32. A7o
	if (include > 204 && 205 > exclude) { Prw1326GetOffSuit(listnum, 12, 5); }
	//33. A3s
	if (include > 208 && 209 > exclude) { Prw1326GetSuit(listnum, 12, 1); }
	//34. KQo
	if (include > 214 && 215 > exclude) { Prw1326GetOffSuit(listnum, 11, 10); }
	//35. A2s
	if (include > 218 && 219 > exclude) { Prw1326GetSuit(listnum, 12, 0); }
	//36. A5o
	if (include > 230 && 231 > exclude) { Prw1326GetOffSuit(listnum, 12, 3); }
	//37. A6o
	if (include > 234 && 235 > exclude) { Prw1326GetOffSuit(listnum, 12, 4); }
	//38. A4o
	if (include > 246 && 247 > exclude) { Prw1326GetOffSuit(listnum, 12, 2); }
	//39. KJo
	if (include > 250 && 251 > exclude) { Prw1326GetOffSuit(listnum, 11, 9); }
	//40. QJs
	if (include > 254 && 255 > exclude) { Prw1326GetSuit(listnum, 10, 9); }


	//41. A3o
	if (include > 258 && 259 > exclude) { Prw1326GetOffSuit(listnum, 12, 1); }
	//42. 22
	if (include > 270 && 271 > exclude) { Prw1326GetPocketPair(listnum, 0); }
	//43. K9s
	if (include > 274 && 275 > exclude) { Prw1326GetSuit(listnum, 11, 7); }
	//44. A2o
	if (include > 286 && 287 > exclude) { Prw1326GetOffSuit(listnum, 12, 0); }
	//45. KTo
	if (include > 290 && 291 > exclude) { Prw1326GetOffSuit(listnum, 11, 8); }
	//46. QTs
	if (include > 294 && 295 > exclude) { Prw1326GetSuit(listnum, 10, 8); }
	//47. K8s
	if (include > 306 && 307 > exclude) { Prw1326GetSuit(listnum, 11, 6); }
	//48. K7s
	if (include > 310 && 311 > exclude) { Prw1326GetSuit(listnum, 11, 5); }
	//49. JTs
	if (include > 310 && 315 > exclude) { Prw1326GetSuit(listnum, 9, 8); }
	//50. K9o
	if (include > 314 && 315 > exclude) { Prw1326GetOffSuit(listnum, 11, 7); }


	//51. K6s
	if (include > 318 && 319 > exclude) { Prw1326GetSuit(listnum, 11, 4); }
	//52. QJo
	if (include > 330 && 331 > exclude) { Prw1326GetOffSuit(listnum, 10, 9); }
	//53. Q9s
	if (include > 336 && 337 > exclude) { Prw1326GetSuit(listnum, 10, 7); }
	//54. K5s
	if (include > 348 && 349 > exclude) { Prw1326GetSuit(listnum, 11, 3); }
	//55. K8o
	if (include > 352 && 353 > exclude) { Prw1326GetOffSuit(listnum, 11, 6); }
	//56. K4s
	if (include > 356 && 357 > exclude) { Prw1326GetSuit(listnum, 11, 2); }
	//57. QTo
	if (include > 360 && 361 > exclude) { Prw1326GetOffSuit(listnum, 10, 8); }
	//58. K7o
	if (include > 372 && 373 > exclude) { Prw1326GetOffSuit(listnum, 11, 5); }
	//59. K3s
	if (include > 384 && 385 > exclude) { Prw1326GetSuit(listnum, 11, 1); }
	//60. K2s
	if (include > 396 && 397 > exclude) { Prw1326GetSuit(listnum, 11, 0); }


	//61. Q8s
	if (include > 408 && 409 > exclude) { Prw1326GetSuit(listnum, 10, 6); }
	//62. K6o
	if (include > 412 && 413 > exclude) { Prw1326GetOffSuit(listnum, 11, 4); }
	//63. J9s
	if (include > 424 && 425 > exclude) { Prw1326GetSuit(listnum, 9, 7); }
	//64. K5o
	if (include > 428 && 429 > exclude) { Prw1326GetOffSuit(listnum, 11, 3); }
	//65. Q9o
	if (include > 432 && 433 > exclude) { Prw1326GetOffSuit(listnum, 10, 7); }
	//66. JTo
	if (include > 436 && 437 > exclude) { Prw1326GetOffSuit(listnum, 9, 8); }
	//67. K4o
	if (include > 448 && 449 > exclude) { Prw1326GetOffSuit(listnum, 11, 2); }
	//68. Q7s
	if (include > 452 && 453 > exclude) { Prw1326GetSuit(listnum, 10, 5); }
	//69. T9s
	if (include > 456 && 457 > exclude) { Prw1326GetSuit(listnum, 8, 7); }
	//70. Q6s
	if (include > 460 && 461 > exclude) { Prw1326GetSuit(listnum, 10, 4); }


	//71. K3o
	if (include > 464 && 465 > exclude) { Prw1326GetOffSuit(listnum, 11, 1); }
	//72. J8s
	if (include > 476 && 477 > exclude) { Prw1326GetSuit(listnum, 9, 6); }
	//73. Q5s
	if (include > 482 && 483 > exclude) { Prw1326GetSuit(listnum, 10, 3); }
	//74. K2o
	if (include > 494 && 495 > exclude) { Prw1326GetOffSuit(listnum, 11, 0); }
	//75. Q8o
	if (include > 506 && 507 > exclude) { Prw1326GetOffSuit(listnum, 10, 6); }
	//76. Q4s
	if (include > 510 && 511 > exclude) { Prw1326GetSuit(listnum, 10, 2); }
	//77. J9o
	if (include > 522 && 523 > exclude) { Prw1326GetOffSuit(listnum, 9, 7); }
	//78. Q3s
	if (include > 526 && 527 > exclude) { Prw1326GetSuit(listnum, 10, 1); }
	//79. T8s
	if (include > 538 && 539 > exclude) { Prw1326GetSuit(listnum, 8, 6); }
	//80. J7s
	if (include > 542 && 543 > exclude) { Prw1326GetSuit(listnum, 9, 5); }


	//81. Q7o
	if (include > 554 && 555 > exclude) { Prw1326GetOffSuit(listnum, 10, 5); }
	//82. Q2s
	if (include > 566 && 567 > exclude) { Prw1326GetSuit(listnum, 10, 0); }
	//83. Q6o
	if (include > 570 && 571 > exclude) { Prw1326GetOffSuit(listnum, 10, 4); }
	//84. 98s
	if (include > 582 && 583 > exclude) { Prw1326GetSuit(listnum, 7, 6); }
	//85. Q5o
	if (include > 586 && 587 > exclude) { Prw1326GetOffSuit(listnum, 10, 3); }
	//86. J8o
	if (include > 590 && 591 > exclude) { Prw1326GetOffSuit(listnum, 9, 6); }
	//87. T9o
	if (include > 594 && 595 > exclude) { Prw1326GetOffSuit(listnum, 8, 7); }
	//88. J6s
	if (include > 598 && 599 > exclude) { Prw1326GetSuit(listnum, 9, 4); }
	//89. T7s
	if (include > 602 && 603 > exclude) { Prw1326GetSuit(listnum, 8, 5); }
	//90. J5s
	if (include > 614 && 615 > exclude) { Prw1326GetSuit(listnum, 9, 3); }


	//91. Q4o
	if (include > 626 && 627 > exclude) { Prw1326GetOffSuit(listnum, 10, 2); }
	//92. J4s
	if (include > 630 && 631 > exclude) { Prw1326GetSuit(listnum, 9, 2); }
	//93. J7o
	if (include > 634 && 635 > exclude) { Prw1326GetOffSuit(listnum, 9, 5); }
	//94. Q3o
	if (include > 640 && 641 > exclude) { Prw1326GetOffSuit(listnum, 10, 1); }
	//95. 97s
	if (include > 644 && 645 > exclude) { Prw1326GetSuit(listnum, 7, 5); }
	//96. T8o
	if (include > 656 && 657 > exclude) { Prw1326GetOffSuit(listnum, 8, 6); }
	//97. J3s
	if (include > 668 && 669 > exclude) { Prw1326GetSuit(listnum, 9, 1); }
	//98. T6s
	if (include > 680 && 681 > exclude) { Prw1326GetSuit(listnum, 8, 4); }
	//99. Q2o
	if (include > 684 && 685 > exclude) { Prw1326GetOffSuit(listnum, 10, 0); }
	//100. J2s
	if (include > 688 && 689 > exclude) { Prw1326GetSuit(listnum, 9, 0); }


	//101. 87s
	if (include > 700 && 701 > exclude) { Prw1326GetSuit(listnum, 6, 5); }
	//102. J6o
	if (include > 704 && 705 > exclude) { Prw1326GetOffSuit(listnum, 9, 4); }
	//103. 98o
	if (include > 708 && 709 > exclude) { Prw1326GetOffSuit(listnum, 7, 6); }
	//104. T7o
	if (include > 720 && 721 > exclude) { Prw1326GetOffSuit(listnum, 8, 5); }
	//105. 96s
	if (include > 724 && 725 > exclude) { Prw1326GetSuit(listnum, 7, 4); }
	//106. J5o
	if (include > 736 && 737 > exclude) { Prw1326GetOffSuit(listnum, 9, 3); }
	//107. T5s
	if (include > 740 && 741 > exclude) { Prw1326GetSuit(listnum, 8, 3); }
	//108. T4s
	if (include > 752 && 753 > exclude) { Prw1326GetSuit(listnum, 8, 2); }
	//109. 86s
	if (include > 756 && 757 > exclude) { Prw1326GetSuit(listnum, 6, 4); }
	//110. J4o
	if (include > 760 && 761 > exclude) { Prw1326GetOffSuit(listnum, 9, 2); }


	//111. T6o
	if (include > 772 && 773 > exclude) { Prw1326GetOffSuit(listnum, 8, 4); }
	//112. 97o
	if (include > 776 && 777 > exclude) { Prw1326GetOffSuit(listnum, 7, 5); }
	//113. T3s
	if (include > 780 && 781 > exclude) { Prw1326GetSuit(listnum, 8, 1); }
	//114. 76s
	if (include > 786 && 787 > exclude) { Prw1326GetSuit(listnum, 5, 4); }
	//115. 95s
	if (include > 798 && 799 > exclude) { Prw1326GetSuit(listnum, 7, 3); }
	//116. J3o
	if (include > 802 && 803 > exclude) { Prw1326GetOffSuit(listnum, 9, 1); }
	//117. T2s
	if (include > 814 && 815 > exclude) { Prw1326GetSuit(listnum, 8, 0); }
	//118. 87o
	if (include > 818 && 819 > exclude) { Prw1326GetOffSuit(listnum, 6, 5); }
	//119. 85s
	if (include > 830 && 831 > exclude) { Prw1326GetSuit(listnum, 6, 3); }
	//120. 96o
	if (include > 842 && 843 > exclude) { Prw1326GetOffSuit(listnum, 7, 4); }


	//121. T5o
	if (include > 846 && 847 > exclude) { Prw1326GetOffSuit(listnum, 8, 3); }
	//122. J2o
	if (include > 850 && 851 > exclude) { Prw1326GetOffSuit(listnum, 9, 0); }
	//123. 75s
	if (include > 862 && 863 > exclude) { Prw1326GetSuit(listnum, 5, 3); }
	//124. 94s
	if (include > 874 && 875 > exclude) { Prw1326GetSuit(listnum, 7, 2); }
	//125. T4o
	if (include > 886 && 887 > exclude) { Prw1326GetOffSuit(listnum, 8, 2); }
	//126. 65s
	if (include > 890 && 891 > exclude) { Prw1326GetSuit(listnum, 4, 3); }
	//127. 86o
	if (include > 894 && 895 > exclude) { Prw1326GetOffSuit(listnum, 6, 4); }
	//128. 93s
	if (include > 906 && 907 > exclude) { Prw1326GetSuit(listnum, 7, 1); }
	//129. 84s
	if (include > 918 && 919 > exclude) { Prw1326GetSuit(listnum, 6, 2); }
	//130. 95o
	if (include > 922 && 923 > exclude) { Prw1326GetOffSuit(listnum, 7, 3); }


	//131. T3o
	if (include > 922 && 923 > exclude) { Prw1326GetOffSuit(listnum, 8, 1); }
	//132. 76o
	if (include > 926 && 927 > exclude) { Prw1326GetOffSuit(listnum, 5, 4); }
	//133. 92s
	if (include > 930 && 931 > exclude) { Prw1326GetSuit(listnum, 7, 0); }
	//134. 74s
	if (include > 942 && 943 > exclude) { Prw1326GetSuit(listnum, 5, 2); }
	//135. 54s
	if (include > 954 && 955 > exclude) { Prw1326GetSuit(listnum, 3, 2); }
	//136. T2o
	if (include > 966 && 967 > exclude) { Prw1326GetOffSuit(listnum, 8, 0); }
	//137. 85o
	if (include > 970 && 971 > exclude) { Prw1326GetOffSuit(listnum, 6, 3); }
	//138. 64s
	if (include > 982 && 983 > exclude) { Prw1326GetSuit(listnum, 4, 2); }
	//139. 85o
	if (include > 986 && 987 > exclude) { Prw1326GetSuit(listnum, 6, 1); }
	//140. 94o
	if (include > 998 && 999 > exclude) { Prw1326GetOffSuit(listnum, 7, 2); }


	//141. 75o
	if (include > 1002 && 1003 > exclude) { Prw1326GetOffSuit(listnum, 5, 3); }
	//142. 82s
	if (include > 1014 && 1015 > exclude) { Prw1326GetSuit(listnum, 6, 0); }
	//143. 73s
	if (include > 1026 && 1027 > exclude) { Prw1326GetSuit(listnum, 5, 1); }
	//144. 93o
	if (include > 1038 && 1039 > exclude) { Prw1326GetOffSuit(listnum, 7, 1); }
	//145. 65o
	if (include > 1042 && 1043 > exclude) { Prw1326GetOffSuit(listnum, 4, 3); }
	//146. 53s
	if (include > 1054 && 1055 > exclude) { Prw1326GetSuit(listnum, 3, 1); }
	//147. 63s
	if (include > 1058 && 1059 > exclude) { Prw1326GetSuit(listnum, 4, 1); }
	//148. 84o
	if (include > 1070 && 1071 > exclude) { Prw1326GetOffSuit(listnum, 6, 2); }
	//149. 92o
	if (include > 1082 && 1083 > exclude) { Prw1326GetOffSuit(listnum, 7, 0); }
	//150. 43s
	if (include > 1086 && 1087 > exclude) { Prw1326GetSuit(listnum, 2, 1); }


	//151. 74o
	if (include > 1098 && 1099 > exclude) { Prw1326GetOffSuit(listnum, 5, 2); }
	//152. 72s
	if (include > 1110 && 1111 > exclude) { Prw1326GetSuit(listnum, 5, 0); }
	//153. 54o
	if (include > 1114 && 1115 > exclude) { Prw1326GetOffSuit(listnum, 3, 2); }
	//154. 64o
	if (include > 1126 && 1127 > exclude) { Prw1326GetOffSuit(listnum, 4, 2); }
	//155. 52s
	if (include > 1138 && 1139 > exclude) { Prw1326GetSuit(listnum, 3, 0); }
	//156. 62s
	if (include > 1150 && 1151 > exclude) { Prw1326GetSuit(listnum, 4, 0); }
	//157. 83o
	if (include > 1162 && 1163 > exclude) { Prw1326GetOffSuit(listnum, 6, 1); }
	//158. 42s
	if (include > 1174 && 1175 > exclude) { Prw1326GetSuit(listnum, 2, 0); }
	//159. 82o
	if (include > 1186 && 1187 > exclude) { Prw1326GetOffSuit(listnum, 6, 0); }
	//160. 73o
	if (include > 1198 && 1199 > exclude) { Prw1326GetOffSuit(listnum, 5, 1); }


	//161. 53o
	if (include > 1210 && include > exclude) { Prw1326GetOffSuit(listnum, 3, 1); }
	//162. 63o
	if (include > 1222 && 1223 > exclude) { Prw1326GetOffSuit(listnum, 4, 1); }
	//163. 32s
	if (include > 1234 && 1235 > exclude) { Prw1326GetSuit(listnum, 1, 0); }
	//164. 43o
	if (include > 1246 && 1247 > exclude) { Prw1326GetOffSuit(listnum, 2, 1); }
	//165. 72o
	if (include > 1258 && 1259 > exclude) { Prw1326GetOffSuit(listnum, 5, 0); }
	//166. 52o
	if (include > 1270 && 1271 > exclude) { Prw1326GetOffSuit(listnum, 3, 0); }
	//167. 62o
	if (include > 1282 && 1283 > exclude) { Prw1326GetOffSuit(listnum, 4, 0); }
	//168. 42o
	if (include > 1294 && 1295 > exclude) { Prw1326GetOffSuit(listnum, 2, 0); }
	//169. 32o
	if (include > 1306 && 1307 > exclude) { Prw1326GetOffSuit(listnum, 1, 0); }
	
}

void COpponentModeling::PrwSetPreflopBottomList(int listnum, double exclude_pct, int weight)
{
	return;
}