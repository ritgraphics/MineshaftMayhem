function raptor.OnInit()
	print("oninit " .. this.GameObject:GetID());
	
	
end

function table_print (tt, indent, done)
  done = done or {}
  indent = indent or 0
  if type(tt) == "table" then
    for key, value in pairs (tt) do
      io.write(string.rep (" ", indent)) -- indent it
      if type (value) == "table" and not done [value] then
        done [value] = true
        io.write(string.format("[%s] => table\n", tostring (key)));
        io.write(string.rep (" ", indent+4)) -- indent it
        io.write("(\n");
        table_print (value, indent + 7, done)
        io.write(string.rep (" ", indent+4)) -- indent it
        io.write(")\n");
      else
        io.write(string.format("[%s] => %s\n",
            tostring (key), tostring(value)))
      end
    end
  else
    io.write(tt .. "\n")
  end
end

function raptor.OnEnable()
	print("onenabled " .. this.GameObject:GetID());
	
	this.timer = 0;
	--table_print(this);
end




function raptor.Update(dt)
	
	go = this.GameObject;
	transform = go:GetTransform();
	transform:RotateX(dt);
	--transform:RotateZ(dt*2);
	
	
	
	this.timer = this.timer + dt;
	--print(this.GameObject:GetID() .. " " .. this.timer);
	if(this.timer > 5) then
		co = go:GetChild(0);
		if(co ~= nil) then 
			--STUFF = this;
			co:SetEnabled(true, false);
			--this = STUFF;
			--print(this.GameObject:GetID());
		end 
	end
end

function raptor.OnDisable()
	print("ondisabled " .. this.GameObject:GetID());
end

function raptor.OnDestroy()
	print("ondestroy " .. this.GameObject:GetID());
end
