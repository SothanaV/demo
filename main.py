from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO, send, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route("/data/<temp>/<humi>")
def getdata(temp,humi):
	print temp
	print humi
	return "OK"
@socketio.on('c2s_com')
def getcom(com):
	print com
@app.route("/home")
def home():
	return render_template('home.html')