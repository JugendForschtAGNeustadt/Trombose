var entfArray = [];
  var lastEntf=0;
  var lastTime=new Date();//
  
  var proximity = new five.Proximity({
    controller: "GP2Y0A21YK",
    pin: "A0"
  });

  proximity.on("data", function() {
      if (entfArray.length==10)
        entfArray.shift();
      entfArray.push(this.cm);
	  var sum = 0;
	  for( var i = 0; i < entfArray.length; i++ ){
          sum += parseInt( entfArray[i], 10 );	
	  }

      var avg = sum/entfArray.length;
	  var pay = {
		  average: 0,
		  lastEntfdiff: 0,
		  length:0
	  }
	  
	  pay.average=avg;
	  pay.lastEntfdiff=Math.abs(lastEntf-avg);
	  pay.length=entfArray.length;
	  var currentTime=new Date();
	  if (Math.abs(lastEntf-avg) > 3 && currentTime-lastTime>200)
	  {
		     node.send({topic: "Avg", payload: JSON.stringify(pay)});
			 lastEntf=avg;
			 lastTime=currentTime;
	  }
		   
  });

