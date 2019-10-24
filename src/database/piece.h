/****************************************************************************
*   Copyright (C) 2015 by Jens Nissen jens-chessx@gmx.net                   *
****************************************************************************/

#ifndef PIECE_H
#define PIECE_H

enum Piece
{
    Empty,
    WhiteKing, WhiteChe, WhiteMa, WhitePao, WhiteShi, WhiteXiang, WhitePawn,
    BlackKing, BlackChe, BlackMa, BlackPao, BlackShi, BlackXiang, BlackPawn,
    ConstPieceTypes,
    InvalidPiece = 255
};

// Pre-Increment
Piece& operator++(Piece& w);

// Post-Increment
Piece operator++(Piece& w, int);

enum PieceType { None, King, Che, Ma, Pao, Shi, Xiang, Pawn };

enum Color {White, Black, NoColor};

/** Return opposite color */
inline Color oppositeColor(Color c)
{
	static const  Color _oppositeColor[] = { Black, White, NoColor};
	//if (c == White) return Black;
 //   else if (c == Black) return White;
 //   return NoColor;
	return _oppositeColor[c];
}

/** Return true if given piece is White */
inline bool isWhite(Piece p)
{
	static const bool _isWhite[] = {
		 false,
	true,  true,  true,  true,  true,  true,   true,
	false, false, false, false, false, false,  false,
	};

	//return p >= WhiteKing && p <= WhitePawn;
	return _isWhite[p];
}

/** Return true if given piece is Black */
inline bool isBlack(Piece p)
{
	static const bool _isBlack[] = {
		 false,
	false, false, false, false, false, false,  false,
	true,  true,  true,  true,  true,  true,   true,
	};
	//return p >= BlackKing && p <= BlackPawn;
	return _isBlack[p];
}

/** Return PieceType of given Piece */
inline PieceType pieceType(Piece p)
{
	static const PieceType _pType[] = {
		None,
		King, Che, Ma, Pao, Shi, Xiang, Pawn,
		King, Che, Ma, Pao, Shi, Xiang, Pawn,
		None
	};
	return _pType[p];
	
	//return PieceType(isWhite(p) ? p : (isBlack(p) ? p - 7 : 0));
}

/** Return Color of given Piece */
inline Color pieceColor(Piece p)
{
	//return isBlack(p) ? Black : White;
	//enum Color { White, Black, NoColor };
	
	static const Color _pColor[] = {
		NoColor,
		White, White, White, White, White, White, White,
		Black, Black, Black, Black, Black, Black, Black,
		NoColor,
	};

	return _pColor[p];
	
}

/** Verify that given Piece is within range */
inline bool isValidPiece(Piece p)
{
    //return isWhite(p) || isBlack(p);

	static const bool _pValid[] = {
	false,
	true,  true,  true,  true,  true,  true,   true,
	true,  true,  true,  true,  true,  true,   true,
	false,
	};

	return _pValid[p];

}

inline Piece flipPiece(Piece p)
{
   
	static const Piece _flipP[] = {
	Empty,
	BlackKing, BlackChe, BlackMa, BlackPao, BlackShi, BlackXiang, BlackPawn,
	WhiteKing, WhiteChe, WhiteMa, WhitePao, WhiteShi, WhiteXiang, WhitePawn,	
	ConstPieceTypes,
	};

	return _flipP [p];
	
	
	//switch (p)
 //   {
 //   case WhiteKing:
 //   case WhiteChe:
 //   case WhiteMa:
 //   case WhitePao:
 //   case WhiteShi:
	//case WhiteXiang:
 //   case WhitePawn:
 //       return Piece((int)p+7);
 //   case BlackKing:
 //   case BlackChe:
 //   case BlackMa:
 //   case BlackPao:
 //   case BlackShi:
	//case BlackXiang:
 //   case BlackPawn:
 //       return Piece((int)p-7);
 //   default:
 //       break;
 //   }
 //   return p;
}

#endif // PIECE_H

