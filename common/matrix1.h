// Matrix1 class
//

#ifndef _Matrix1_H_
#define _Matrix1_H_


class File;

/********FRAN*******/
#include "Algebra3.h"
/********FRAN*******/

class Matrix1
{
 public:
  Matrix1 ();
//  Matrix1 (const double *mat);
  Matrix1 (const double *mat);
  Matrix1 (const double *rot, const double *pos);
  ~Matrix1();

  void FileSave (File& file) const;
  void FileLoad (File& file);

  void FromPacked (const double *mat);
  void FromFloat (const double* mat);
  void FromLDraw (const double *f);
  void FromEulerAngles (double yaw, double pitch, double roll);
  void FromAxisAngle (const double *axis, double angle);

  void ToLDraw (double *f) const;
  void ToEulerAngles (double *rot) const;
  void ToAxisAngle (double *rot) const;

  void LoadIdentity ();
  void Translate (double x, double y, double z);
  void Multiply (Matrix1& m1, Matrix1& m2);
  bool Invert ();

  void GetTranslation(double *x, double *y, double *z);
  void SetTranslation(double x, double y, double z);
  void GetTranslation(double pos[3]);
  void SetTranslation(double pos[3]);

  void TransformPoint(double out[], const double in[3]);
  void TransformPoints (double p[], int n);
  void Create (double mx, double my, double mz, double rx, double ry, double rz);
  void CreateOld(double mx, double my, double mz, double rx, double ry, double rz);
  void Rotate(double angle, double x, double y, double z);
  void RotateCenter(double angle, double x, double y, double z, double px, double py, double pz);
  bool FromInverse(double* src);
  void CreatePerspective (double fovy, double aspect, double nearval, double farval);
  void CreateLookat (const double *eye, const double *target, const double *up);

  /**********FRAN*********/
//  void crear(sirMat4d matriz);
  void crear(double *matriz);
  void crearx(double *matriz);
  void modificarmat();
  /**********FRAN*********/

 public:
  double m[16];
};

#endif //_Matrix1_H_
