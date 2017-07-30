from flask import Flask, render_template, request, jsonify     			
from flask_socketio import SocketIO, send, emit									

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)
relay_com = "0"
relay_com2 = "0"

@app.route("/data/<temp>/<humi>")
def getdata(temp,humi):
	global relay_com
	print("Temperature:%s Humidity:%s"%(temp,humi))
	socketio.emit('s2c_temp',temp)
	socketio.emit('s2c_humi',humi)
	return relay_com

@app.route("/data2/<temp2>/<humi2>")
def getdata2(temp2,humi2):
	global relay_com2
	print("Temperature2:%s Humidity2:%s"%(temp2,humi2))
	socketio.emit('s2c_temp2',temp2)
	socketio.emit('s2c_humi2',humi2)
	return relay_com2


@socketio.on('c2s_com')
def getcom(com):
	global relay_com
	if(com=="onrelay"):
		relay_com = "1"
	if(com=="offrelay"):
		relay_com = "0"
	print (com)
	
@app.route("/home")
def home():
	return render_template('home.html')