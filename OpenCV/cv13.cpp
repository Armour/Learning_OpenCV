#include "my_cv.h"

static void fast(void) {
    Mat descriptors1; Mat descriptors2;
    Mat img_keypoints_1; Mat img_keypoints_2;
    //Mat srcImageFast1 = imread("/Users/armour/Desktop/OpenCV/Image/Blob1.jpg", CV_LOAD_IMAGE_COLOR);
    //Mat srcImageFast2 = imread("/Users/armour/Desktop/OpenCV/Image/Blob2.jpg", CV_LOAD_IMAGE_COLOR);
    Mat srcImageFast1 = imread("/Users/armour/Desktop/OpenCV/Image/Comp1.jpg", CV_LOAD_IMAGE_COLOR);
    Mat srcImageFast2 = imread("/Users/armour/Desktop/OpenCV/Image/Comp2.jpg", CV_LOAD_IMAGE_COLOR);

    //imshow("Original1", srcImage1);
    //imshow("Original2", srcImage2);

    vector<KeyPoint> keypoints_1, keypoints_2;		//vector模板类是能够存放任意类型的动态数组，能够增加和压缩数据
    FastFeatureDetector fast(40);	//定义一个FastFeatureDetector（FAST） 特征检测类对象
    fast.detect(srcImageFast1, keypoints_1);
    fast.detect(srcImageFast2, keypoints_2);

    //drawKeypoints(srcImageSift1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    //drawKeypoints(srcImageSift2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    drawKeypoints(srcImageFast1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(srcImageFast2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("Sift1", img_keypoints_1);
    imshow("Sift2", img_keypoints_2);

    SiftDescriptorExtractor siftDesc;
    siftDesc.compute(srcImageFast1, keypoints_1, descriptors1);
    siftDesc.compute(srcImageFast2, keypoints_2, descriptors2);


    //===============================================================================================================
    // BruteForce Match (not good)
    BruteForceMatcher<L2<float>>matcher_bf;
    vector<DMatch> matches_bf;
    matcher_bf.match(descriptors1, descriptors2, matches_bf);

    nth_element(matches_bf.begin(), matches_bf.begin() + 24, matches_bf.end());
    matches_bf.erase(matches_bf.begin() + 25, matches_bf.end());

    Mat imageMatches_bf;
    drawMatches(srcImageFast1, keypoints_1, srcImageFast2, keypoints_2, matches_bf, imageMatches_bf, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("Fast_SiftMatch_BruteForce", imageMatches_bf);


    //===============================================================================================================
    // FLANN Match
    FlannBasedMatcher matcher_flann;
    vector<DMatch> matches_flann;
    matcher_flann.match(descriptors1, descriptors2, matches_flann);

    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors1.rows; i++ ) {
        double dist = matches_flann[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.
    std::vector<DMatch> good_matches;

    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches_flann[i].distance < 2 * min_dist)
            good_matches.push_back( matches_flann[i]);
    }

    //-- Draw only "good" matches
    Mat imageMatches_flann;
    drawMatches( srcImageFast1, keypoints_1, srcImageFast2, keypoints_2,
                good_matches, imageMatches_flann, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Show detected matches
    imshow( "Fast_SiftMatch_Flann", imageMatches_flann );


    //===============================================================================================================
    //-- Localize the object from srcImageSurf1 in srcImageSurf2
    /*std::vector<Point2f> obj;
     std::vector<Point2f> scene;

     for( int i = 0; i < good_matches.size(); i++ )
     {
     //-- Get the keypoints from the good matches
     obj.push_back( keypoints_1[ good_matches[i].queryIdx ].pt );
     scene.push_back( keypoints_2[ good_matches[i].trainIdx ].pt );
     }

     Mat H = findHomography(obj, scene, CV_RANSAC);

     //-- Get the corners from the image_1 ( the object to be "detected" )
     Point2f obj_corners[4] = { cvPoint(0,0), cvPoint( srcImageSift1.cols, 0 ), cvPoint( srcImageSift1.cols, srcImageSift1.rows ), cvPoint( 0, srcImageSift1.rows ) };
     Point scene_corners[4];

     //-- Map these corners in the scene ( image_2)
     for( int i = 0; i < 4; i++ )
     {
     double x = obj_corners[i].x;
     double y = obj_corners[i].y;

     double Z = 1./( H.at<double>(2,0)*x + H.at<double>(2,1)*y + H.at<double>(2,2) );
     double X = ( H.at<double>(0,0)*x + H.at<double>(0,1)*y + H.at<double>(0,2) )*Z;
     double Y = ( H.at<double>(1,0)*x + H.at<double>(1,1)*y + H.at<double>(1,2) )*Z;
     scene_corners[i] = cvPoint( cvRound(X) + srcImageSift1.cols, cvRound(Y) );
     }

     Mat imageMatches_flann_obj = imageMatches_flann.clone();

     //-- Draw lines between the corners (the mapped object in the scene - image_2 )
     line( imageMatches_flann_obj, scene_corners[0], scene_corners[1], Scalar( 0, 255, 0), 2 );
     line( imageMatches_flann_obj, scene_corners[1], scene_corners[2], Scalar( 0, 255, 0), 2 );
     line( imageMatches_flann_obj, scene_corners[2], scene_corners[3], Scalar( 0, 255, 0), 2 );
     line( imageMatches_flann_obj, scene_corners[3], scene_corners[0], Scalar( 0, 255, 0), 2 );

     //-- Show detected matches
     imshow( "SurfMatch_Flann & Object detection", imageMatches_flann_obj );
     */
    
    waitKey(0);
}

static void sift(void) {
    Mat descriptors1; Mat descriptors2;
    Mat img_keypoints_1; Mat img_keypoints_2;
    //Mat srcImageSift1 = imread("/Users/armour/Desktop/OpenCV/Image/Blob1.jpg", CV_LOAD_IMAGE_COLOR);
    //Mat srcImageSift2 = imread("/Users/armour/Desktop/OpenCV/Image/Blob2.jpg", CV_LOAD_IMAGE_COLOR);
    Mat srcImageSift1 = imread("/Users/armour/Desktop/OpenCV/Image/Comp1.jpg", CV_LOAD_IMAGE_COLOR);
    Mat srcImageSift2 = imread("/Users/armour/Desktop/OpenCV/Image/Comp2.jpg", CV_LOAD_IMAGE_COLOR);

    //imshow("Original1", srcImage1);
    //imshow("Original2", srcImage2);

    vector<KeyPoint> keypoints_1, keypoints_2;		//vector模板类是能够存放任意类型的动态数组，能够增加和压缩数据
    SiftFeatureDetector Sift(0.05);	//定义一个SiftFeatureDetector（SIFT） 特征检测类对象
    Sift.detect(srcImageSift1, keypoints_1);
    Sift.detect(srcImageSift2, keypoints_2);

    //drawKeypoints(srcImageSift1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    //drawKeypoints(srcImageSift2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    drawKeypoints(srcImageSift1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(srcImageSift2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("Sift1", img_keypoints_1);
    imshow("Sift2", img_keypoints_2);

    SiftDescriptorExtractor siftDesc;
    siftDesc.compute(srcImageSift1, keypoints_1, descriptors1);
    siftDesc.compute(srcImageSift2, keypoints_2, descriptors2);


    //===============================================================================================================
    // BruteForce Match (not good)
    BruteForceMatcher<L2<float>>matcher_bf;
    vector<DMatch> matches_bf;
    matcher_bf.match(descriptors1, descriptors2, matches_bf);

    nth_element(matches_bf.begin(), matches_bf.begin() + 24, matches_bf.end());
    matches_bf.erase(matches_bf.begin() + 25, matches_bf.end());

    Mat imageMatches_bf;
    drawMatches(srcImageSift1, keypoints_1, srcImageSift2, keypoints_2, matches_bf, imageMatches_bf, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("Sift_SiftMatch_BruteForce", imageMatches_bf);


    //===============================================================================================================
    // FLANN Match
    FlannBasedMatcher matcher_flann;
    vector<DMatch> matches_flann;
    matcher_flann.match(descriptors1, descriptors2, matches_flann);

    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors1.rows; i++ ) {
        double dist = matches_flann[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.
    std::vector<DMatch> good_matches;

    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches_flann[i].distance < 2 * min_dist)
            good_matches.push_back( matches_flann[i]);
    }

    //-- Draw only "good" matches
    Mat imageMatches_flann;
    drawMatches( srcImageSift1, keypoints_1, srcImageSift2, keypoints_2,
                good_matches, imageMatches_flann, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Show detected matches
    imshow( "Sift_SiftMatch_Flann", imageMatches_flann );


    //===============================================================================================================
    //-- Localize the object from srcImageSurf1 in srcImageSurf2
    /*std::vector<Point2f> obj;
    std::vector<Point2f> scene;

    for( int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints_1[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_2[ good_matches[i].trainIdx ].pt );
    }

    Mat H = findHomography(obj, scene, CV_RANSAC);

    //-- Get the corners from the image_1 ( the object to be "detected" )
    Point2f obj_corners[4] = { cvPoint(0,0), cvPoint( srcImageSift1.cols, 0 ), cvPoint( srcImageSift1.cols, srcImageSift1.rows ), cvPoint( 0, srcImageSift1.rows ) };
    Point scene_corners[4];

    //-- Map these corners in the scene ( image_2)
    for( int i = 0; i < 4; i++ )
    {
        double x = obj_corners[i].x;
        double y = obj_corners[i].y;

        double Z = 1./( H.at<double>(2,0)*x + H.at<double>(2,1)*y + H.at<double>(2,2) );
        double X = ( H.at<double>(0,0)*x + H.at<double>(0,1)*y + H.at<double>(0,2) )*Z;
        double Y = ( H.at<double>(1,0)*x + H.at<double>(1,1)*y + H.at<double>(1,2) )*Z;
        scene_corners[i] = cvPoint( cvRound(X) + srcImageSift1.cols, cvRound(Y) );
    }

    Mat imageMatches_flann_obj = imageMatches_flann.clone();

    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    line( imageMatches_flann_obj, scene_corners[0], scene_corners[1], Scalar( 0, 255, 0), 2 );
    line( imageMatches_flann_obj, scene_corners[1], scene_corners[2], Scalar( 0, 255, 0), 2 );
    line( imageMatches_flann_obj, scene_corners[2], scene_corners[3], Scalar( 0, 255, 0), 2 );
    line( imageMatches_flann_obj, scene_corners[3], scene_corners[0], Scalar( 0, 255, 0), 2 );

    //-- Show detected matches
    imshow( "SurfMatch_Flann & Object detection", imageMatches_flann_obj );
     */

    waitKey(0);
}

static void surf(void) {
    Mat descriptors1; Mat descriptors2;
    Mat img_keypoints_1; Mat img_keypoints_2;
    Mat srcImageSurf1 = imread("/Users/armour/Desktop/can/fd.jpg", CV_LOAD_IMAGE_COLOR);
    Mat srcImageSurf2 = imread("/Users/armour/Desktop/can/6.jpg", CV_LOAD_IMAGE_COLOR);

    //imshow("Original1", srcImage1);
    //imshow("Original2", srcImage2);

    int minHessian = 400;	//定义SURF中的hessian阈值特征点检测算子
    vector<KeyPoint> keypoints_1, keypoints_2;		//vector模板类是能够存放任意类型的动态数组，能够增加和压缩数据
    SurfFeatureDetector surf(minHessian);	//定义一个SurfFeatureDetector（SURF） 特征检测类对象
    surf.detect(srcImageSurf1, keypoints_1);
    surf.detect(srcImageSurf2, keypoints_2);

    //drawKeypoints(srcImageSurf1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    //drawKeypoints(srcImageSurf2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    drawKeypoints(srcImageSurf1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(srcImageSurf2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("Surf1", img_keypoints_1);
    imshow("Surf2", img_keypoints_2);

    SurfDescriptorExtractor surfDesc;
    surfDesc.compute(srcImageSurf1, keypoints_1, descriptors1);
    surfDesc.compute(srcImageSurf2, keypoints_2, descriptors2);


    //===============================================================================================================
    // BruteForce Match (not good)
    BruteForceMatcher<L2<float>>matcher_bf;
    vector<DMatch> matches_bf;
    matcher_bf.match(descriptors1, descriptors2, matches_bf);

    nth_element(matches_bf.begin(), matches_bf.begin() + 24, matches_bf.end());
    matches_bf.erase(matches_bf.begin() + 25, matches_bf.end());

    Mat imageMatches_bf;
    drawMatches(srcImageSurf1, keypoints_1, srcImageSurf2, keypoints_2, matches_bf, imageMatches_bf, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("Surf_SurfMatch_BruteForce", imageMatches_bf);


    //===============================================================================================================
    // FLANN Match
    FlannBasedMatcher matcher_flann;
    vector<DMatch> matches_flann;
    matcher_flann.match(descriptors1, descriptors2, matches_flann);

    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors1.rows; i++ ) {
        double dist = matches_flann[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.
    std::vector<DMatch> good_matches;

    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches_flann[i].distance < 2 * min_dist)
            good_matches.push_back( matches_flann[i]);
    }

    //-- Draw only "good" matches
    Mat imageMatches_flann;
    drawMatches( srcImageSurf1, keypoints_1, srcImageSurf2, keypoints_2,
                good_matches, imageMatches_flann, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    
    //-- Show detected matches  
    imshow( "Surf_SurfMatch_Flann", imageMatches_flann );


    //===============================================================================================================
    //-- Localize the object from srcImageSurf1 in srcImageSurf2
    std::vector<Point2f> obj;
    std::vector<Point2f> scene;

    for( int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints_1[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_2[ good_matches[i].trainIdx ].pt );
    }

    Mat H = findHomography(obj, scene, CV_RANSAC);

    //-- Get the corners from the image_1 ( the object to be "detected" )
    Point2f obj_corners[4] = { cvPoint(0,0), cvPoint( srcImageSurf1.cols, 0 ), cvPoint( srcImageSurf1.cols, srcImageSurf1.rows ), cvPoint( 0, srcImageSurf1.rows ) };
    Point scene_corners[4];

    //-- Map these corners in the scene ( image_2)
    for( int i = 0; i < 4; i++ )
    {
        double x = obj_corners[i].x;
        double y = obj_corners[i].y;

        double Z = 1./( H.at<double>(2,0)*x + H.at<double>(2,1)*y + H.at<double>(2,2) );
        double X = ( H.at<double>(0,0)*x + H.at<double>(0,1)*y + H.at<double>(0,2) )*Z;
        double Y = ( H.at<double>(1,0)*x + H.at<double>(1,1)*y + H.at<double>(1,2) )*Z;
        scene_corners[i] = cvPoint( cvRound(X) + srcImageSurf1.cols, cvRound(Y) );
    }

    Mat imageMatches_flann_obj = imageMatches_flann.clone();

    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    line( imageMatches_flann_obj, scene_corners[0], scene_corners[1], Scalar( 0, 255, 0), 2 );
    line( imageMatches_flann_obj, scene_corners[1], scene_corners[2], Scalar( 0, 255, 0), 2 );
    line( imageMatches_flann_obj, scene_corners[2], scene_corners[3], Scalar( 0, 255, 0), 2 );
    line( imageMatches_flann_obj, scene_corners[3], scene_corners[0], Scalar( 0, 255, 0), 2 );
    
    //-- Show detected matches
    imshow( "Surf_SurfMatch_Flann & Object detection", imageMatches_flann_obj );

    waitKey(0);
}

static void mser(void) {
    Mat descriptors1; Mat descriptors2;
    Mat img_keypoints_1; Mat img_keypoints_2;
    Mat srcImageMser1 = imread("/Users/armour/Desktop/OpenCV/Image/Comp1.jpg", CV_LOAD_IMAGE_COLOR);
    Mat srcImageMser2 = imread("/Users/armour/Desktop/OpenCV/Image/Comp2.jpg", CV_LOAD_IMAGE_COLOR);
    //Mat srcImageMser1 = imread("/Users/armour/Desktop/OpenCV/Image/Blob1.jpg", CV_LOAD_IMAGE_COLOR);
    //Mat srcImageMser2 = imread("/Users/armour/Desktop/OpenCV/Image/Blob2.jpg", CV_LOAD_IMAGE_COLOR);

    //imshow("Original1", srcImage1);
    //imshow("Original2", srcImage2);

    vector<KeyPoint> keypoints_1, keypoints_2;		//vector模板类是能够存放任意类型的动态数组，能够增加和压缩数据
    MserFeatureDetector mser;	//定义一个MserFeatureDetector（MSER） 特征检测类对象
    mser.detect(srcImageMser1, keypoints_1);
    mser.detect(srcImageMser2, keypoints_2);

    //drawKeypoints(srcImageSift1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    //drawKeypoints(srcImageSift2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    drawKeypoints(srcImageMser1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(srcImageMser2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("Mser1", img_keypoints_1);
    imshow("Mser2", img_keypoints_2);

    SiftDescriptorExtractor siftDesc;
    siftDesc.compute(srcImageMser1, keypoints_1, descriptors1);
    siftDesc.compute(srcImageMser2, keypoints_2, descriptors2);


    //===============================================================================================================
    // BruteForce Match (not good)
    BruteForceMatcher<L2<float>>matcher_bf;
    vector<DMatch> matches_bf;
    matcher_bf.match(descriptors1, descriptors2, matches_bf);

    nth_element(matches_bf.begin(), matches_bf.begin() + 24, matches_bf.end());
    matches_bf.erase(matches_bf.begin() + 25, matches_bf.end());

    Mat imageMatches_bf;
    drawMatches(srcImageMser1, keypoints_1, srcImageMser2, keypoints_2, matches_bf, imageMatches_bf, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("Mser_Sift_Match_BruteForce", imageMatches_bf);


    //===============================================================================================================
    // FLANN Match
    FlannBasedMatcher matcher_flann;
    vector<DMatch> matches_flann;
    matcher_flann.match(descriptors1, descriptors2, matches_flann);

    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors1.rows; i++ ) {
        double dist = matches_flann[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.
    std::vector<DMatch> good_matches;

    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches_flann[i].distance < 2 * min_dist)
            good_matches.push_back( matches_flann[i]);
    }

    //-- Draw only "good" matches
    Mat imageMatches_flann;
    drawMatches( srcImageMser1, keypoints_1, srcImageMser2, keypoints_2,
                good_matches, imageMatches_flann, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Show detected matches
    imshow( "Mser_SiftMatch_Flann", imageMatches_flann );
    waitKey(0);
}

static void simpleBlob(void) {

    Mat descriptors1; Mat descriptors2;
    Mat img_keypoints_1; Mat img_keypoints_2;
    Mat srcImageBlob1 = imread("/Users/armour/Desktop/OpenCV/Image/Blob1.jpg", CV_LOAD_IMAGE_COLOR);
    Mat srcImageBlob2 = imread("/Users/armour/Desktop/OpenCV/Image/Blob2.jpg", CV_LOAD_IMAGE_COLOR);

    //imshow("Original1", srcImage1);
    //imshow("Original2", srcImage2);

    vector<KeyPoint> keypoints_1, keypoints_2;		//vector模板类是能够存放任意类型的动态数组，能够增加和压缩数据
    SimpleBlobDetector::Params params;
    //params.minThreshold = 10;
    //params.maxThreshold = 100;
    //params.thresholdStep = 10;
    //params.minArea = 10;
    //params.minConvexity = 0.3;
    //params.minInertiaRatio = 0.01;
    //params.maxArea = 8000;
    //params.maxConvexity = 10;
    //params.filterByColor = true;
    //params.filterByCircularity = true;
    SimpleBlobDetector blob(params);
    blob.detect(srcImageBlob1, keypoints_1);
    blob.detect(srcImageBlob2, keypoints_2);

    //drawKeypoints(srcImageSift1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    //drawKeypoints(srcImageSift2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DEFAULT);
    drawKeypoints(srcImageBlob1, keypoints_1, img_keypoints_1, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(srcImageBlob2, keypoints_2, img_keypoints_2, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    imshow("Blob1", img_keypoints_1);
    imshow("Blob2", img_keypoints_2);

    SiftDescriptorExtractor siftDesc;
    siftDesc.compute(srcImageBlob1, keypoints_1, descriptors1);
    siftDesc.compute(srcImageBlob2, keypoints_2, descriptors2);


    //===============================================================================================================
    // BruteForce Match (not good)
    BruteForceMatcher<L2<float>>matcher_bf;
    vector<DMatch> matches_bf;
    matcher_bf.match(descriptors1, descriptors2, matches_bf);

    nth_element(matches_bf.begin(), matches_bf.begin() + 24, matches_bf.end());
    matches_bf.erase(matches_bf.begin() + 25, matches_bf.end());

    Mat imageMatches_blob;
    drawMatches(srcImageBlob1, keypoints_1, srcImageBlob2, keypoints_2, matches_bf, imageMatches_blob, Scalar::all(-1),
                Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("Blob_SiftMatch_BruteForce", imageMatches_blob);


    //===============================================================================================================
    // FLANN Match
    FlannBasedMatcher matcher_flann;
    vector<DMatch> matches_flann;
    matcher_flann.match(descriptors1, descriptors2, matches_flann);

    double max_dist = 0;
    double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors1.rows; i++ ) {
        double dist = matches_flann[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
    //-- PS.- radiusMatch can also be used here.
    std::vector<DMatch> good_matches;

    for (int i = 0; i < descriptors1.rows; i++) {
        if (matches_flann[i].distance < 2 * min_dist)
            good_matches.push_back( matches_flann[i]);
    }

    //-- Draw only "good" matches
    Mat imageMatches_flann;
    drawMatches( srcImageBlob1, keypoints_1, srcImageBlob2, keypoints_2,
                good_matches, imageMatches_flann, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Show detected matches
    imshow( "Blob_SiftMatch_Flann", imageMatches_flann );
    waitKey(0);
}

void cv13(void) {
    //图片命名:局部图像特征检测算子+特征向量描述算子+高维特征向量匹配方法
    //fast();         //角点检测
    //sift();
    surf();
    //mser();         //最大稳定极值区域
    //simpleBlob();   //斑点检测
    /*StarFeatureDetector;
    DenseFeatureDetector;
    GridAdaptedFeatureDetector;
    DynamicAdaptedFeatureDetector;
    PyramidAdaptedFeatureDetector;*/
    /*GoodFeatureToTrackDetector gftt (500,	// maximum number of corners to be returned
                                       0.01,	// quality level
                                       10);	// minimum allowed distance between points*/
}

/*
"FAST" – FastFeatureDetector
"STAR" – StarFeatureDetector
"SIFT" – SIFT (nonfree module)
"SURF" – SURF (nonfree module)
"ORB" – ORB
"MSER" – MSER
"GFTT" – GoodFeaturesToTrackDetector
"HARRIS" – GoodFeaturesToTrackDetector with Harris detector enabled
"Dense" – DenseFeatureDetector
"SimpleBlob" – SimpleBlobDetector
*/