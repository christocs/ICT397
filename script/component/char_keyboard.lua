function update(evt)
    local upd8 = evt:to_update()
    local speed = 5.0
    local dt = upd8.delta
    local vel = speed * dt
    local cur_cam = camera.current()
    local new_pos = cur_cam.pos
    if keyboard.is_pressed(key.W) then
        local r = cur_cam:front()
        r.y = 0
        new_pos = cur_cam.pos:add(r:normalized():smul(vel))
    end
    if keyboard.is_pressed(key.S) then
        local r = cur_cam:front()
        r.y = 0
        new_pos = cur_cam.pos:sub(r:normalized():smul(vel))
    end
    if keyboard.is_pressed(key.A) then
        local r = cur_cam:right()
        r.y = 0
        new_pos = cur_cam.pos:sub(r:normalized():smul(vel))
    end
    if keyboard.is_pressed(key.D) then
        local r = cur_cam:right()
        r.y = 0
        new_pos = cur_cam.pos:add(r:normalized():smul(vel))
    end
    local terrain_height = terrain.height_at(cur_cam.pos.x, cur_cam.pos.z) - 8
    cur_cam.pos = vector3(new_pos.x, terrain_height, new_pos.z)
end

this:register_event(event.update, update)
