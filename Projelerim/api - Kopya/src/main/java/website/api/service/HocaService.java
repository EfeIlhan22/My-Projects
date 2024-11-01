package website.api.service;

import java.util.List;

import website.api.dto.HocaDto;

public interface HocaService {
    HocaDto createHoca(HocaDto hocaDto);

    List<HocaDto> getAllHocas();

    HocaDto getHocaById(int id);

    HocaDto updateHocaById(HocaDto hocaDto , int id);

    void deleteHocaById(int id);
}
