package website.api.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;

import website.api.model.Yorum;


public interface  YorumRepository extends JpaRepository<Yorum, Integer> {
    List<Yorum> findByHocaId(int hoca_id);
}
