
function game.OnInit()
	
end

function game.OnEnable()
   
end

function game.Update(dt)
  
    if Input.SingleKeyPress(IKEY.ESC) or Input.SingleKeyPress(IKEY.F2) then
        Game.Exit();
    end

end

function game.OnDisable()
	
end

function game.OnDestroy()
	
end
