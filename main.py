from flask import Flask, render_template, request, jsonify     			
from flask_socketio import SocketIO, send, emit									

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)
relay_com = "0"

@app.route("/data/<temp>/<humi>")
def getdata(temp,humi):
	global relay_com
	print temp
	print humi
	return relay_com
@socketio.on('c2s_com')
def getcom(com):
	global relay_com
	if(relay_com=="onrelay"):
		relay_com = "1"
	print com
@app.route("/home")
def home():
	return render_template('home.html')