#! /usr/bin/python
 
# import the necessary packages
from imutils.video import VideoStream
from imutils.video import FPS
import face_recognition
import imutils
import pickle
import time
import cv2
import RPi.GPIO as GPIO

RELAY = 17
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(RELAY, GPIO.OUT)
GPIO.output(RELAY,GPIO.LOW)
 
currentname = "unknown"
encodingsP = "encodings.pickle"
cascade = "haarcascade_frontalface_default.xml"
 
print("[INFO] loading encodings + face detector…")
data = pickle.loads(open(encodingsP, "rb").read())
detector = cv2.CascadeClassifier(cascade)
 
print("[INFO] starting video stream…")
vs = VideoStream(src=0).start()
time.sleep(2.0)
 
fps = FPS().start()
 
prevTime = 0
doorUnlock = False
 
while True:

 frame = vs.read()
 frame = imutils.resize(frame, width=500)

 gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
 rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
 
 rects = detector.detectMultiScale(gray, scaleFactor=1.1,
 minNeighbors=5, minSize=(30, 30),
 flags=cv2.CASCADE_SCALE_IMAGE)
 
 boxes = [(y, x + w, y + h, x) for (x, y, w, h) in rects]
 
 encodings = face_recognition.face_encodings(rgb, boxes)
 names = []
 
 # loop over the facial embeddings
 for encoding in encodings:
    matches = face_recognition.compare_faces(data["encodings"],
    encoding)
    name = "Unknown" 
    if True in matches:
      matchedIdxs = [i for (i, b) in enumerate(matches) if b]
      counts = {}
  
      # to unlock the door
      GPIO.output(RELAY,GPIO.HIGH)
      prevTime = time.time()
      doorUnlock = True
      print("door unlock")
  
 
 for i in matchedIdxs:
    name = data["names"][i]
    counts[name] = counts.get(name, 0) + 1
  
 name = max(counts, key=counts.get)
 
 #If someone in your dataset is identified, print their name on the screen
 if currentname != name:
    currentname = name
    print(currentname)
 
 # update the list of names
 names.append(name)
 
 #lock the door after 5 seconds
 if doorUnlock == True and time.time() - prevTime > 5:
   doorUnlock = False
   GPIO.output(RELAY,GPIO.LOW)
   print("door lock")
 
 # loop over the recognized faces
 for ((top, right, bottom, left), name) in zip(boxes, names):
 # draw the predicted face name on the image – color is in BGR
  cv2.rectangle(frame, (left, top), (right, bottom),
  (0, 255, 0), 2)
  y = top - 15 if top - 15 > 15 else top + 15
  cv2.putText(frame, name, (left, y), cv2.FONT_HERSHEY_SIMPLEX,
  .8, (255, 0, 0), 2)
  
  # display the image to our screen
  cv2.imshow("Facial Recognition is Running", frame)
  key = cv2.waitKey(1) & 0xFF
 
 # quit when 'q' key is pressed
 if key == ord("q"):
  break
 
 # update the FPS counter
 fps.update()
 
# stop the timer and display FPS information
fps.stop()
print("[INFO] elasped time: {:.2f}".format(fps.elapsed()))
print("[INFO] approx. FPS: {:.2f}".format(fps.fps()))
 
# do a bit of cleanup
cv2.destroyAllWindows()
vs.stop()