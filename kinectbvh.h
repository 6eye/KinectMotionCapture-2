#ifndef KINECTBVH_H
#define KINECTBVH_H

#define SCALE 100
#define FPS 0.033333
#define PI 3.14159265

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>

#include <windows.h>
#include <NuiApi.h>
#include <vector>
#include <map>
#include <Eigen>

using namespace std;
using namespace Eigen;

struct KinectJoint
{
	Matrix3f transform;
	Vector4 quaternion;
	Vector3f angles;
};

/**
* Manipule les donn�es de la Kinect que la classe KinectSkeleton a envoy� et g�n�re le fichier BVH r�sultant de la capture de mouvements
*/
class KinectBVH : public QObject
{
	Q_OBJECT

public:
	/**
	* Constructeur
	*/
	KinectBVH();
	/**
	* Destructeur
	*/
	~KinectBVH();

	/**
	* Ajoute un offset � la description du BVH
	*/
	void AddOffset(int, const Vector4 &);
	/**
	* Ajoute un squelette et ses informations pour les donn�es de la capture de mouvements
	*/
	void AddBonesOrientation(KinectJoint *);
	/**
	* Ajoute une position du joint Hip Center pour les donn�es de la capture de mouvements
	*/
	void AddPosition(const Vector4 &);
	/**
	* Incr�mente le nombre de frames
	*/
	void IncrementNbFrames();
	/**
	* Cr�� un nouveau fichier en fonction du nom re�u en param�tre, renvoi true si r�ussi sinon false
	*/
	bool CreateBVHFile(QString);
	/**
	* G�n�re le fichier BVH
	*/
	void FillBVHFile();
private:
	// Fichier
	QFile *m_pFile;

	// Offsets
	Vector4 m_aOffsets[20];
	// Positions du Hip Center
	vector<Vector4> m_vPositions;
	// Squelettes et leurs informations des joints
	vector<KinectJoint*> m_vBonesOrientation;

	// Nombre de frames
	int m_nbFrame;

	/**
	* G�n�re la description du squelette pour le BVH
	*/
	void CreateSkeletonInformation();
	/**
	* G�n�re les donn�es des mouvements pour le BVH
	*/
	void CreateMotionInformation();
	/**
	* Convertis un quaternion pass� en param�tre en angles d'Euler, renvoi un tableau contenant les 3 angles
	*/
	int *QuaternionToEulerAngles(const Vector4 &);
};

#endif // KINECTBVH_H
