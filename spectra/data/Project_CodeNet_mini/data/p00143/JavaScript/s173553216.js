// const
var COUNTER_CLOCKWISE = 1;
var CLOCKWISE = - 1;
var ONLINE_BACK = 2;
var ONLINE_FRONT =  -2;
var ON_SEGMENT = 0;

// Vector2d
var Vector2D = class Vector2D {
	constructor(x,y){
		this.x = x;
		this.y = y;
	}
}

Vector2D.prototype.Init = function(x,y){
	this.x = x;
	this.y = y;
}

/*
 * v: Vector2D
 */
function rotateVector90(v){
	var r = new Vector2D();
	r.x = -v.y;
	r.y = v.x;
	return r;
}

/*
 * get degree to radian return radian
 */
function getDegreeToRadian(degree){
	var pi = 3.14159265358979323846;
	return degree * pi / 180;
}

/*
 * vec:Vector2D return Vector2D
 */
function getRotateVector(vec,degree){
	var radian = getDegreeToRadian(degree);

	var sin = Math.sin(radian);
	var cos = Math.cos(radian);

	var r = new Vector2D();
	r.x = vec.x * cos - vec.y * sin;
	r.y = vec.x * sin + vec.y * cos;

	return r;
}

/*
 * vec:Vector2D return Vector2D
 */
function getRotateVectorFromRad(vec,radian){
	var sin = Math.sin(radian);
	var cos = Math.cos(radian);

	var r = new Vector2D();
	r.x = vec.x * cos - vec.y * sin;
	r.y = vec.x * sin + vec.y * cos;

	return r;
}

function isEqualVectors(a,b){
	return equalFloats(a.x - b.x,0) && equalFloats(a.y - b.y,0);
}

/**
 * vec:Vector2D
 * 
 * return unitVector
 */
function getUnitVector(vec){
	var length = getVectorLength2D(vec);
	if(length > 0){
		return getDivideVector(vec,length);
	}
	return vec;
}

/**
 * return vector length
 * 
 * vec:Vector2D
 */
function getVectorLength2D(vec){
	return Math.sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

function getNorm(vec){
	return vec.x * vec.x + vec.y * vec.y;
}

function getDivideVector(vec2D,length){
    var vec = new Vector2D();
	vec.x = vec2D.x / length;
	vec.y = vec2D.y / length;
	return vec;
}

function equalFloats(a,b){
	var threshold = 1 / 8192;
	return Math.abs(a - b) < threshold;
}

function isParallelVector(vectorA,vectorB){
	var na = rotateVector90(vectorA);
	return equalFloats(0,dotProduct2D(na,vectorB));
}

function isVerticalVector(vectorA,vectorB){
	return equalFloats(0,dotProduct2D(vectorA,vectorB));
}

function subtractVector(vecA,vecB){
	var vec = new Vector2D();
	vec.x = vecA.x - vecB.x;
	vec.y = vecA.y - vecB.y;
	return vec;
}

function dotProduct2D(vecA,vecB){
    var dot = vecA.x * vecB.x + vecA.y * vecB.y;
	return vecA.x * vecB.x + vecA.y * vecB.y;
}

/**
 * 外積
 * 
 * @param vecA
 * @param vecB
 * @returns
 */
function getCross(vecA,vecB){
	return vecA.x * vecB.y - vecA.y * vecB.x;
}

/**
 * line segment
 * 
 * point1:Vector2D point2:Vector2D
 */
var LineSegment2D = class LineSegment2D {
	constructor(point1,point2){
		this.point1 = point1;
		this.point2 = point2;
	}
}

LineSegment2D.prototype.Init = function(point1,point2){
	this.point1 = point1;
	this.point2 = point2;
}

function onOneSide(axis,segment){
	var d1 = new Vector2D();
	d1 = subtractVector(segment.point1,axis.base);

	var d2 = new Vector2D();
	d2 = subtractVector(segment.point2,axis.base);

	var n = new Vector2D();
	n = rotateVector90(axis.direction);

	// 同じ方向だということを返す
	return dotProduct2D(n,d1) * dotProduct2D(n,d2) > 0;
}

function overLapping(minA,maxA,minB,maxB){
	return minB <= maxA && minA <= maxB;
}

function isSegmentsCollide(segment1,segment2){
	// 線分の方向をチェックするためのベクトル
	var axisA = new Line();
	var axisB = new Line();

	// 線分1のベクトルに対して、線分2が片側にあるかチェック
	axisA.base = segment1.point1;
	axisA.direction = subtractVector(segment1.point2,segment1.point1);

	if(onOneSide(axisA,segment2)){
		return false;
	}

	// 同じく
	axisB.base = segment2.point1;
	axisB.direction = subtractVector(segment2.point2,segment2.point1);

	if(onOneSide(axisB,segment1)){
		return false;
	}

	// 同じベクトルをもつケース
	if(isParallelVector(axisA.direction,axisB.direction)){
		var rangeA = getProjectSegment(segment1,axisA.direction);
		var rangeB = getProjectSegment(segment2,axisA.direction);

		// 重なっているか
		return isOverLappingRanges(rangeA,rangeB);
	}
	else{
		return true;
	}
}

/*
 * Line Object
 */
function Line(){
	// vector2D
	this.base;
	// vector2D
	this.direction
}

Line.prototype.Init = function(base,direction,color){
	this.base = base;
	this.direction = direction;
}

/**
 * Range
 */
var Range = class Range {
	constructor(min,max){
		this.min = min;
		this.max = max;
	}
}

function getMaxMinRange(range1,range2){
	var range = new Range();
	range.min = range1.min < range2.min ? range1.min : range2.min;
	range.max = range1.max < range2.max ? range2.max : range1.max;
	return range;
}

function getSortRange(range){
	var sorted = new Range(range.min,range.max);
	if(range.min > range.max){
		sorted.min = range.max;
		sorted.max = range.min;
	}
	return sorted;
}

function getNegateVector(vector){
	vector.x = -vector.x;
	vector.y = -vector.y;
	return vector;
}

function addVector(vecA,vecB){
	return new Vector2D(vecA.x + vecB.x,vecA.y + vecB.y);
}

/**
 * segment:segment onto:Vector2D
 * 
 * return Range
 */
function getProjectSegment(segment,onto){
	var ontoUnitVec = getUnitVector(onto);

	var range = new Range();
	range.min = dotProduct2D(ontoUnitVec,segment.point1);
	range.max = dotProduct2D(ontoUnitVec,segment.point2);

	range = getSortRange(range);
	return range;
}

function isOverLappingRanges(range1,range2){
	return overLapping(range1.min,range1.max,range2.min,range2.max);
}

function projectVector(project,onto){
	var d = dotProduct2D(onto,onto);
	if(0 < d){
	    var dp = dotProduct2D(project,onto);
	    return multiplyVector(onto,dp / d);
	}
	return onto;
}

/**
 * point class
 */
var Point2D = class Point2D {
	constructor(x,y){
		this.x = x;
		this.y = y;

	}
}

function addPoint(point1,point2){
	return new Point2D(point1.x + point2.x,point1.y + point2.y);
}

function subtractPoint(point1,point2){
	return new Point2D(point1.x - point2.x,point1.y - point2.y);
}

function multiplyPoint(point,scalar){
	return new Point2D(point.x * scalar,point.y * scalar);
}

/**
 * segment : LineSegment2D
 * point : Point
 */
function getProjectPoint(segment,point){
	var vec1 = new Vector2D(segment.point2.x - segment.point1.x,segment.point2.y - segment.point1.y);
	var vec2 = new Vector2D(point.x - segment.point1.x,point.y - segment.point1.y);
	var rate = dotProduct2D(vec2,vec1) / getNorm(vec1);
	var vec3 = multiplyVector(vec1,rate);
	var project = new Point2D(segment.point1.x + vec3.x,segment.point1.y + vec3.y);
	return project; 
}

function getReflectionPoint(segment,point){
	var projection = getProjectPoint(segment,point);
	// pから射影点までのベクトル
	var vec = subtractPoint(projection,point);
	// 2倍したものが射影点になる
	var refrectionPoint = multiplyPoint(vec,2);
	// 始点を足す
	return addPoint(refrectionPoint,point);
}

/**
 * 
 * @param segment1
 * @param segment2
 * @returns point
 */
function getCrossPoint(segment1,segment2){
	// 基準となる線を決める
	var baseVector = new Vector2D(segment2.point2.x - segment2.point1.x,segment2.point2.y - segment2.point1.y);
	var d1Vec = new Vector2D(segment1.point1.x - segment2.point1.x,segment1.point1.y - segment2.point1.y);
	var d2Vec = new Vector2D(segment1.point2.x - segment2.point1.x,segment1.point2.y - segment2.point1.y);
	var d1 = Math.abs(getCross(baseVector,d1Vec));
	var d2 = Math.abs(getCross(baseVector,d2Vec));
	var t = d1 / (d1 + d2);
	var x = segment1.point1.x + (segment1.point2.x - segment1.point1.x) * t;
	var y = segment1.point1.y + (segment1.point2.y - segment1.point1.y) * t;
	return new Point2D(x,y);
}

function multiplyVector(vec,scalar){
	var temp = new Vector2D();
	temp.x = vec.x * scalar;
	temp.y = vec.y * scalar;
	return temp;
}

function clampOnRange(x,min,max){
	if(x < min){
		return min;
	}else if(x > max){
		return max;
	}else{
		return x;
	}
}

/**
 * 直線と点との距離
 */
function getDistanceLinePoint(line,point){
	var vec1 = new Vector2D(line.point2.x - line.point1.x,line.point2.y - line.point1.y);
	var vec2 = new Vector2D(point.x - line.point1.x,point.y - line.point1.y);
	return Math.abs(getCross(vec1,vec2) / getVectorLength2D(vec1)); 
}

/**
 * 線分と点との距離を求める
 */
function getDistanceSegmentPoint(segment,point){    
	// ベクトルp2 - p1とベクトルp - p1がなす角θが90どより大きい場合(-90より小さい場合)
	// dは点pと点p1の距離になる
	if(dotProduct2D(subtractPoint(segment.point2,segment.point1),subtractPoint(point,segment.point1)) < 0){
		return getVectorLength2D(subtractPoint(point,segment.point1));
	}
	// ベクトルp1 - p2とベクトルp - p2がなす角θが90どより大きい場合(-90より小さい場合)
	// dは点pと点p2の距離になる
	if(dotProduct2D(subtractPoint(segment.point1,segment.point2),subtractPoint(point,segment.point2)) < 0){
		return getVectorLength2D(subtractPoint(point,segment.point2));
	}
	// それ以外はdは点pと直線p1p2の距離になる
	return getDistanceLinePoint(segment,point);
}

/**
 * 線分と線分との距離を求める
 */
function getSegmentDistance(segment1,segment2){
	// 交差していた場合距離は0になる
	if(isSegmentsCollide(segment1,segment2)){
		return 0;
	}
	return Math.min(Math.min(getDistanceSegmentPoint(segment1,segment2.point1),getDistanceSegmentPoint(segment1,segment2.point2)),
			Math.min(getDistanceSegmentPoint(segment2,segment1.point1),getDistanceSegmentPoint(segment2,segment1.point2)));
}

function ccw(point1,point2,point3){
    var vec1 = new Vector2D(point2.x - point1.x,point2.y - point1.y);
    var vec2 = new Vector2D(point3.x - point1.x,point3.y - point1.y);
    var cross = getCross(vec1,vec2);

    if(cross > Number.EPSILON){
        return COUNTER_CLOCKWISE;
    }
    if(cross < -Number.EPSILON){
        return CLOCKWISE;
    }
    if(dotProduct2D(vec1,vec2) < -Number.EPSILON){
        return ONLINE_BACK;
    }
    if(getVectorLength2D(vec1) < getVectorLength2D(vec2)){
        return ONLINE_FRONT;
    }
    return ON_SEGMENT;
}

/**
 * アンドリューでconvex hollを返す 
*/
function getConvexHoll(points){
    if(points.length < 3){
        return points;
    }
    
    // xを基準に昇順にソート、数値が同じものはyが小さいもの基準にソート 
    points.sort((a, b) => (a.x > b.x) ? 1 : (a.x == b.x) ? ((a.y > b.y) ? 1 : -1) : -1);
    // xを小さいほうから2つ
    var u = [];
    u.push(points[0]);
    u.push(points[1]);
    // xを大きい方から2つ
    var l = [];
    l.push(points[points.length - 1]);
    l.push(points[points.length - 2]);
    
    // 上部の生成
    for(var i = 2;i < points.length;++i){
    	// 対象が半時計なら削除する
        for(var j = u.length;j >= 2 && ccw(u[j - 2],u[j - 1],points[i]) == COUNTER_CLOCKWISE;--j){
            u.pop();
        }
        u.push(points[i]);
    }
    // 下部の生成
    for(var i = points.length - 3;i >= 0;--i){
    	// 対象が半時計なら削除する
        for(var j = l.length;j >= 2 && ccw(l[j - 2],l[j - 1],points[i]) == COUNTER_CLOCKWISE;--j){
            l.pop();;
        }
        l.push(points[i]);
    }
    // 時計回りに凸包の点の列を生成
    l.reverse();
    for(var i = u.length - 2;i >= 1;--i){
        l.push(u[i]);
    }
    return l;
}

function getConvexDiameter(points){
	// 対心点(p,q)を取る(y軸で最小・最大のもの)
    var is = 0;
    var js = 0;
    for(var i = 1; i < points.length; i++){
      if(points[i].y > points[is].y) is = i;
      if(points[i].y < points[js].y) js = i;
    }
    var distance = getNorm(subtractVector(points[is],points[js]));
    var maxi = is,i = js,maxj = js,j = js;
    do {
        // 対心点の中で最長距離のものを探す
      if(getCross(subtractVector(points[(i + 1) % points.length],points[i]),subtractVector(points[(j + 1) % points.length],points[j])) >= 0){
        j = (j + 1) % points.length;
      } else {
        i = (i + 1) % points.length;
      }
      if(getNorm(subtractVector(points[i],points[j])) > distance){
        distance = getNorm(subtractVector(points[i],points[j]));
        maxi = i;
        maxj = j;
      }
    }  while (i != is || j != js);
    return distance;
}

/**
 * 点で構成される多角形の2d面積を返す
 * 
 */
function getArea(points){
    var area = 0;
    for(var i = 0;i < points.length;++i){
        area += getCross(points[i],points[(i + 1) % points.length]);
    }
    return area / 2;
}

function getConvexCut(points,point1,point2){
    // 切り取られた多角形
    var convex = [];
    
	for(var i = 0; i < points.length;++i){
		var nowPoint = points[i];
		var nextPoint = points[(i + 1) % points.length];
		var nowPointCcw = ccw(point1,point2,nowPoint);
		if(nowPointCcw != CLOCKWISE){
		    convex.push(nowPoint);
		}
		if(nowPointCcw * ccw(point1,point2,nextPoint) == CLOCKWISE){
		    // 交点を求める
		  var crossPoint = getCrossPointFromPoints(point1,point2,nowPoint,nextPoint);
		  convex.push(crossPoint);
		}
	}
	return convex;
}

function getPointDistance(point1,point2){
	var x = point1.x - point2.x;
	var y = point1.y - point2.y;
	return Math.sqrt(x * x + y * y);
}

function closestPair(points,n){
	if (n == 1)  return Number.MAX_SAFE_INTEGER;
	var d = Number.MAX_SAFE_INTEGER;
	var m = Math.floor(n / 2);
	d = Math.min(closestPair(points, m),closestPair(points.slice(m),n - m));
    var mx = points[m].x;
	var arr = [];
    
	for (var i = m;i >= 0;--i){
	    var x = Math.abs(points[i].x - mx);
		if (x > d){
		    break;
		}
		else{
		    arr.push(points[i]);
		}
	}
	for (var i = m + 1; i < n; ++i){
		if (Math.abs(points[i].x - mx) > d){
		    break;
		}	
		else{
            arr.push(points[i]);  
		} 
	}
	arr.sort((a, b) => (a.y > b.y) ? 1 : -1);

	for(var i = 0;i < arr.length;++i){
		for (var j = i + 1;j < arr.length && Math.abs(arr[j].y - arr[i].y) < d;++j){
		    var tmp = getPointDistance(arr[i],arr[j]);
			if (tmp < d) d = tmp;
		}
	}
	return d;
}

/**
 * 2d円を表すクラス
 * 
 */
var Circle2D = class Circle2D {
	constructor(x,y,r){
		this.center = new Point2D(x,y);
		this.r = r;
	}
}

/**
 * 円と直線の交点を返す
 * 
 */
function getCircleLineCrossPoints(line,circle){
	var d = getDistanceLinePoint(line,circle.center);
	// 交点がない場合
	if(d > circle.r){
	    console.log("return")
		return;
	}
	// 円の中心から直線への射影点
	var pr = getProjectPoint(line,circle.center);
	// 交点が一つ
	if(equalFloats(d,circle.r)){
        // 射影点が交点になる
		return pr;
	}
	// 交点が2つ
	else{
	    // 直線の単位ベクトルを求める
	    var unit = getUnitVector(new Vector2D(line.point1.x - line.point2.x,line.point1.y - line.point2.y));
	    // 射影点から交点までの長さを求める
	    var length = Math.sqrt((circle.r * circle.r) - getNorm(subtractVector(pr,circle.center)));
	    var crossPoints = [];
	    crossPoints[0] = addPoint(pr,multiplyVector(unit,length));
	    crossPoints[1] = subtractVector(pr,multiplyVector(unit,length));
        return crossPoints;
	}
}

/**
 * 極点を返す
 * 
*/
function getPolar(a,r){
    return new Point2D(Math.cos(r) * a,Math.sin(r) * a);
}

/*
 * 円と円との交点を求める 
 */
function getCircleCircleCrossPoints(circle1,circle2){
    var crossPoints = [];
    // 円の中心との距離
    var d = getPointDistance(circle1.center,circle2.center);
    var rDis = circle1.r + circle2.r;
    // 交点がない
    if(d > rDis){
        return;
    }
    // 交点が一つ
    else if(equalFloats(d == rDis)){
        // 点と点のベクトルを求める
        var vec = new Vector2D(circle2.center.x - circle1.center.x,circle2.center.y - circle1.center.y);
        // 単位ベクトル
        var unit = getUnitVector(vec);
        var point = multiplyVector(unit,d);
        crossPoints[0] = crossPoints[1] = point;
    }
    else{
        // 中心点1から中心点2の線分と交点との角度aを余弦を使って求める
        var a = Math.acos((circle1.r * circle1.r + d * d - circle2.r * circle2.r) / (2 * circle1.r * d));
        // 中心点1を通るy = 0の直線とaとの差分の角度をtとする
        var vec = subtractVector(circle2.center,circle1.center);
        var t = Math.atan2(vec.y,vec.x);
        
        crossPoints[0] = addPoint(circle1.center,getPolar(circle1.r,t + a));
        crossPoints[1] = addPoint(circle1.center,getPolar(circle1.r,t - a));
    }
    return crossPoints;
}

/**
 * 円と点との接戦の交点を求める
 */
function getTangentsFromPoint(circle,point){
  var base = subtractPoint(point,circle.center);
  var baseLength = getVectorLength2D(base);
  var radian = Math.acos(circle.r / baseLength);
  var vec1 = getDivideVector(base,baseLength);
  vec1 = multiplyVector(vec1,circle.r);
  var points = [];
  points[0] = addPoint(circle.center,getRotateVectorFromRad(vec1,radian));
  points[1] = addPoint(circle.center,getRotateVectorFromRad(vec1,-radian));
  return points;
}

function get3PointCross(point1,point2,point3){
    var vec1 = new Vector2D(point2.x - point1.x,point2.y - point1.y);
    var vec2 = new Vector2D(point3.x - point1.x,point3.y - point1.y);
    var cross = getCross(vec1,vec2);
    return cross;
}

function inTriangle(p1,p2,p3,p){
    let ccw1 = get3PointCross(p1,p2,p);
    let ccw2 = get3PointCross(p2,p3,p);
    let ccw3 = get3PointCross(p3,p1,p);
    
    if(ccw1 > 0 && ccw2 > 0 && ccw3 > 0 || ccw1 < 0 && ccw2 < 0 && ccw3 < 0){
        return true;
    }
    return false;
}

var input = require('fs').readFileSync('/dev/stdin', 'utf8');
let arr = (input.trim()).split("\n");
arr.shift()

for(var i = 0;i < arr.length;++i){
    let ans = "NG"
    var numbers = arr[i].split(" ").map(Number);
    var p1 = new Point2D(numbers[0],numbers[1]);
    var p2 = new Point2D(numbers[2],numbers[3]);
    var p3 = new Point2D(numbers[4],numbers[5]);
    var p4  = new Point2D(numbers[6],numbers[7]);
    var p5  = new Point2D(numbers[8],numbers[9]);
    // 三角形のある点の対辺がその点と対象の点と同じ位置にある場合
    if(inTriangle(p1,p2,p3,p4) ^ inTriangle(p1,p2,p3,p5)){
        ans = "OK"
    }
    console.log(ans);
}

